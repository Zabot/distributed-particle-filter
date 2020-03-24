import numpy
import shutil

from ctypes import cdll, c_void_p, POINTER

from library_types import Message

class SwarmNode:
    def __init__(self, nodeID):
        self.position = numpy.zeros(3)
        self.velocity = numpy.zeros(3)
        self.nodeId = nodeID

        # We have to copy the library into a tempfile to force it to be reloaded
        # as a new instance by dlopen since there is global state for each node
        # (This is a dirty hack, but its the only transparent way to wrap the
        # micro code in a simulator)
        tmpfile = '/tmp/libmicrocontroller' + str(nodeID) + '.so'
        shutil.copyfile('libmicrocontroller.so', tmpfile)

        self.libmicrocontroller = cdll.LoadLibrary(tmpfile)

        self.libmicrocontroller.set_node_id(nodeID)
        self.libmicrocontroller.init()

        self.libmicrocontroller.get_tx_queue.restype = POINTER(Message)

        self.c_vec = numpy.random.uniform(0, 1, 3)


    def update(self, nodes):
        self.libmicrocontroller.loop()

        tx_count = self.libmicrocontroller.get_tx_queue_length()
        tx_pointer = self.libmicrocontroller.get_tx_queue()

        tx_queue = [tx_pointer[i] for i in range(0, tx_count)]

        for m in tx_queue:
            for n in nodes:
                d = numpy.linalg.norm(n.position - self.position)
                if d < 10:
                    if n is self:
                        continue

                    m.range = d
                    if n.libmicrocontroller.add_pending_rx_message(m):
                        print("Dropped message, {} rx buffer full"
                              .format(n.nodeId))

        self.libmicrocontroller.clear_tx_queue()


    def get_particle_filter(self):
        return c_void_p.in_dll(self.libmicrocontroller, 'pfPointer')


    def get_triliteration_data(self):
        return c_void_p.in_dll(self.libmicrocontroller, 'dataPointer')

