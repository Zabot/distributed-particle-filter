import numpy
import random

from argparse import ArgumentParser
from argparse import FileType

from nodefile import parse, dump
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
parser.add_argument("-p",
                    dest="position_count",
                    default=0,
                    help="number of randomly selected position aware nodes",
                    type=int)
args = parser.parse_args()

# Load a nodefile from arguments
if args.nodefile:
    nodes = parse(args.nodefile)

else:
    nodes = [SwarmNode(i, args.range) for i in range(1, args.count + 1)]

    for n in nodes:
        n.position = numpy.random.uniform(-10, 10, 3)
        n.position[2] = 0

    for n in random.sample(nodes, args.position_count):
        n.position_interval = 1

# Run the simulation
sim = Simulation(nodes)
with Window("Composite", 1000, 1000, 30) as composite:
    try:
        while True:
            print("Stats: {}".format(sim.stats()))

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

            if len(cargs) > 0:
                if cargs[0].startswith("@"):
                    cluster = int(cargs[0][1:])
                    selected = [n for n in nodes if n.get_cluster() == cluster]
                else:
                    selected = [nodes[int(cargs[0]) - 1]]
            else:
                selected = nodes

            # Clear the window
            if command == 'c':
                composite.clear()
                composite.drawAxes()

            # Draw the position of a single node
            if command == 'p':
                for n in selected:
                    composite.drawPosition(n,
                            int(cargs[1]) if cargs[1:] else False)

            # Display a single node, or display all nodes
            if command == 'd':
                for n in selected:
                    composite.drawNode(n, int(cargs[1]) if cargs[1:] else args.triliteration)

            # Update a specific node, or update the next node in the filter
            if command == 'n':
                if selected is nodes:
                    updated = sim.step(None)

                    if updated == nodes[0]:
                        composite.clear()
                        composite.drawAxes()

                    composite.drawNode(updated, args.triliteration)
                else:
                    for n in selected:
                        updated = sim.step(n)

                        if updated == nodes[0]:
                            composite.clear()
                            composite.drawAxes()

                        composite.drawNode(updated, args.triliteration)

            if command == 's':
                dump("saved.yaml", nodes)

            if command == 'r':
                iterations = sim.run_to_convergance()

                composite.clear()
                composite.drawAxes()
                for n in nodes:
                    composite.drawNode(n, int(cargs[1]) if cargs[1:] else args.triliteration)

                print("Converged in {} stats: {}".format(iterations, sim.stats()))

            composite.render()

    except KeyboardInterrupt:
        print("Exiting...")

