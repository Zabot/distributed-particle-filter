from visualization import Window
from nodefile import dump

# Commands:
# c -- Clear the visualization window
# p <node> <show_range> -- Draw the real position and comm range of a node
# r <node> <show_trilat> -- Draw the particle filter and neighbors of a node
# n <node> -- Update a node and render it
# s -- Save the simulation to saved.yaml
# g -- run the simulation to convergence
def run(sim, view = 30, name = "Composite"):
    with Window(name, 1000, 1000, view) as composite:
        try:
            while True:
                print("Stats: {}".format(sim.stats()))

                i = input("?>").split(' ')

                # No command was given, advance the simulation
                if len(i) == 1 and i[0] == '':
                    sim.advance()

                    composite.clear()
                    composite.drawAxes()
                    for n in sim.nodes:
                        composite.drawNode(n)
                    composite.render()
                    continue

                command, *cargs = i

                if len(cargs) > 0:
                    if cargs[0].startswith("@"):
                        cluster = int(cargs[0][1:])
                        selected = [n for n in sim.nodes if n.get_cluster() == cluster]
                    else:
                        selected = [sim.nodes[int(cargs[0]) - 1]]
                else:
                    selected = sim.nodes

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
                if command == 'r':
                    for n in selected:
                        composite.drawNode(n, int(cargs[1]) if cargs[1:] else True)

                # Update a specific node, or update the next node in the filter
                if command == 'n':
                    # If no node was selected, tell the simulation to step the
                    # next node in the queue
                    if selected is sim.nodes:
                        updated, new_step = sim.step()

                        if new_step:
                            composite.clear()
                            composite.drawAxes()

                        composite.drawNode(updated, False)
                    else:
                        for n in selected:
                            updated, new_step = sim.step(n)

                            if new_step:
                                composite.clear()
                                composite.drawAxes()

                            composite.drawNode(updated, False)

                if command == 's':
                    dump("saved.yaml", sim.nodes)

                if command == 'g':
                    iterations = sim.run_to_convergance()

                    composite.clear()
                    composite.drawAxes()
                    for n in sim.nodes:
                        composite.drawNode(n, int(cargs[1]) if cargs[1:] else False)

                    print("Converged in {} stats: {}".format(iterations, sim.stats()))

                composite.render()

        except KeyboardInterrupt:
            print("Exiting...")
