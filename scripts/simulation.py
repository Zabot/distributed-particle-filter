import random

class Simulation:
    def __init__(self, nodes):
        self.nodes = nodes

        self.pending = random.sample(nodes, len(nodes))

    def advance(self):
        while not self.step()[1]:
            pass

    def step(self, n = None):
        if n is None:
            n = self.pending[0]

        n.update(self.nodes)
        if n in self.pending:
            self.pending.remove(n)
        else:
            raise ValueError("Node cannot be stepped")

        # If there are no more pending nodes, reset
        if not self.pending:
            self.pending = random.sample(self.nodes, len(self.nodes))
            return n, True

        return n, False

