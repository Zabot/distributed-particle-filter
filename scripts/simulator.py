import numpy
import random

from argparse import ArgumentParser
from argparse import FileType

from nodefile import parse
from simulation import Simulation
from swarm_node import SwarmNode
from visualization import Window

# Argument parsing
parser = ArgumentParser()
parser.add_argument("-f",
                    dest="nodefile",
                    default=None,
                    help="node file name",
                    type=FileType('r'))
parser.add_argument("-c",
                    dest="count",
                    default=10,
                    help="number of nodes (exclusive with nodefile)",
                    type=int)
parser.add_argument("-r",
                    dest="range",
                    default=10,
                    help="node communication rnage",
                    type=float)
parser.add_argument("-t",
                    dest="triliteration",
                    action="store_true",
                    help="Display triliteration rings")
args = parser.parse_args()

# Load a nodefile from arguments
if args.nodefile:
    nodes = parse(args.nodefile)

else:
    nodes = [SwarmNode(i, args.range) for i in range(1, args.count + 1)]

    for n in nodes:
        n.position = numpy.random.uniform(-10, 10, 3)
        n.position[2] = 0

# Run the simulation
sim = Simulation(nodes)
with Window("Composite", 1000, 1000, 30) as composite:
    try:
        while True:
            i = input("?>").split(' ')

            # No command was given, advance the simulation
            if len(i) == 1 and i[0] == '':
                sim.advance()

                composite.clear()
                composite.drawAxes()
                for n in nodes:
                    composite.drawNode(n)
                composite.render()
                continue

            command, *cargs = i
            selected = nodes[int(cargs[0]) - 1] if len(cargs) > 0 else None

            # Clear the window
            if command == 'c':
                composite.clear()
                composite.drawAxes()

            # Draw the position of a single node
            if command == 'p':
                if selected:
                    composite.drawPosition(selected)
                else:
                    for n in nodes:
                        composite.drawPosition(n)

            # Render a single node, or render all nodes
            if command == 'r':
                if selected:
                    composite.drawNode(selected, True)
                else:
                    for n in nodes:
                        composite.drawNode(n, args.triliteration)

            # Update a specific node, or update the next node in the filter
            if command == 'n':
                if sim.step(selected):
                    composite.clear()
                    composite.drawAxes()

                composite.drawNode(n, args.triliteration)

            composite.render()

    except KeyboardInterrupt:
        print("Exiting...")

