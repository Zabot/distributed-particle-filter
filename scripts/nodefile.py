import yaml
import numpy

from swarm_node import SwarmNode

def parse(f):
    nodes = []
    data = yaml.load(f, Loader=yaml.Loader)

    for p in data['nodes']:
        position = numpy.array([p['x'], p['y'], p['z']])

        n = SwarmNode(1 + len(nodes), data['range'])
        n.position = position
        nodes.append(n)

    return nodes

