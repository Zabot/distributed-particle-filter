import numpy
import random

from argparse import ArgumentParser
from argparse import FileType

from nodefile import parse
from simulation import Simulation
from simulator_window import run
from swarm_node import SwarmNode

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
parser.add_argument("-g",
                    dest="convergence",
                    action="store_true",
                    help="Run to convergance without displaying")
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

if args.convergence:
    iterations = sim.run_to_convergance()
    print("{}, {}, {}".format(iterations, *sim.stats()))

else:
    run(sim)

