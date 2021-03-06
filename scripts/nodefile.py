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
        try:
            n.position_interval = p['position_interval']
        except KeyError:
            n.position_interval = 0
        nodes.append(n)

    return nodes

def dump(f, nodes):
    data = {'nodes': [], 'range': nodes[0].range}
    for n in nodes:
        data['nodes'].append({
            'x': float(n.position[0]),
            'y': float(n.position[1]),
            'z': float(n.position[2]),
            'position_interval': n.position_interval
        })

    with open(f, 'w') as outfile:
        s = yaml.dump(data, outfile)

