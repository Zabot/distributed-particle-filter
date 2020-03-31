from ctypes import cdll, c_void_p, POINTER, pointer

from library_types import vector3f, LogicalScreenGeometry, VisualizationWindow

vis = cdll.LoadLibrary('./libvisualization.so')

vis.drawParticleFilter.argtypes = [
        c_void_p,
        POINTER(LogicalScreenGeometry),
        c_void_p,
        POINTER(vector3f),
    ]

vis.drawTriliterationData.argtypes = [
        c_void_p,
        POINTER(LogicalScreenGeometry),
        c_void_p,
        POINTER(vector3f),
    ]

vis.drawAxes.argtypes = [
        c_void_p,
        POINTER(LogicalScreenGeometry)
    ]

class Window(object):
    def __init__(self, name, width, height, bounds = 30):
        self.name = name.encode('utf-8')
        self.window = VisualizationWindow(
                LogicalScreenGeometry(
                    width,
                    height,
                    bounds,
                    bounds,
                    int(width / 2),
                    int(height / 2)
                ))

    def __enter__(self):
        vis.initalizeVisualizationWindow(pointer(self.window), self.name)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        vis.destroyVisualizationWindow(pointer(self.window));

    def drawAxes(self):
        vis.drawAxes(self.window.renderer, pointer(self.window.geometry))

    def render(self):
        vis.renderVisualizationWindow(pointer(self.window));

    def clear(self):
        vis.clearVisualizationWindow(pointer(self.window))

    def drawNode(self, node, triliteration = False):
        color = vector3f(*node.c_vec)

        # Draw the particle filter
        pf_pointer = node.get_particle_filter()
        vis.drawParticleFilter(self.window.renderer,
                               pointer(self.window.geometry),
                               pf_pointer, pointer(color))

        # Draw the triliteration circles if desired
        if triliteration:
            data_pointer = node.get_triliteration_data()
            vis.drawTriliterationData(self.window.renderer,
                                      pointer(self.window.geometry),
                                      data_pointer,
                                      pointer(color))
