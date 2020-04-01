import random

class Simulation:
    def __init__(self, nodes):
        self.nodes = nodes

        self.pending = set(nodes)

    def advance(self):
        while not self.step():
            pass

    def step(self, n = None):
        if n is None:
            n = random.choice(tuple(self.pending))

        if n in self.pending:
            n.update(self.nodes)
            self.pending.remove(n)
        else:
            raise ValueError("Node cannot be stepped")

        # If there are no more pending nodes, reset
        if not self.pending:
            self.pending = set(self.nodes)
            return True

        return False

