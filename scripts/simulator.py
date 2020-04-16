import numpy
import random
import time

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
parser.add_argument("-s",
                    default=0,
                    dest="seed",
                    help="Seed for all in simulation randomness",
                    type=int)
parser.add_argument("-m",
                    default=int(time.time() * 256),
                    dest="cluster",
                    help="Seed used for the generation of a random cluster",
                    type=int)
args = parser.parse_args()

# Seed the random number sequence used for color generation so node color is
# consistent
numpy.random.seed(0)

# Load a nodefile from arguments
if args.nodefile:
    nodes = parse(args.nodefile)

else:
    nodes = [SwarmNode(i, args.range) for i in range(1, args.count + 1)]

    # Seed PRNG sequence used for assigning node positions
    numpy.random.seed(args.cluster)
    for n in nodes:
        n.position = numpy.random.uniform(-10, 10, 3)
        n.position[2] = 0

    # Seed PRNG used to select which nodes are global position aware
    random.seed(args.seed)
    for n in random.sample(nodes, args.position_count):
        n.position_interval = 1

# Seed PRNG used for simulation
random.seed(args.seed)

# Run the simulation
sim = Simulation(nodes)

if args.convergence:
    iterations = sim.run_to_convergance()
    print("{}, {}, {}".format(iterations, *sim.stats()))

else:
    run(sim)

