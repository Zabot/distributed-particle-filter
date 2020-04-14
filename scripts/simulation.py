import random

import numpy

class Simulation:
    def __init__(self, nodes):
        self.nodes = nodes

        self.pending = random.sample(nodes, len(nodes))

    def advance(self):
        while not self.step()[1]:
            pass

    def step(self, n = None):
        # If there are no more pending nodes, start a new step
        new_step = False
        if not self.pending:
            self.pending = random.sample(self.nodes, len(self.nodes))
            new_step = True

        if n is None:
            n = self.pending[0]

        n.update(self.nodes)
        if n in self.pending:
            self.pending.remove(n)
        else:
            raise ValueError("Node cannot be stepped")

        return n, new_step

    def stats(self):
        errors = [n.get_error() ** 2 for n in self.nodes]
        confidences = [n.get_confidence() for n in self.nodes]
        return numpy.average(errors), numpy.average(confidences)

    def run_to_convergance(self, confidence = 0.9):
        iteration = 0

        while numpy.average([n.get_confidence() for n in self.nodes]) < confidence:
            self.advance()
            iteration += 1

            if iteration > 100:
                return iteration

        return iteration
