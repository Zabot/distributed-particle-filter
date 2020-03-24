import numpy
from visualization import Window

from swarm_node import SwarmNode

nodeCount = 4
nodes = [SwarmNode(i) for i in range(1, nodeCount + 1)]

for n in nodes:
    n.position = numpy.random.uniform(-5, 5, 3)
    n.position[2] = 0

with Window("Composite", 1000, 1000) as composite:
    try:
        while True:
            composite.clear()
            composite.drawAxes()
            for n in nodes:
                n.update(nodes)
                composite.drawNode(n, True)

            composite.render()
            input("Press Enter to continue...")

    except KeyboardInterrupt:
        print("Exiting...")

