from ctypes import c_float, c_int, c_short, c_void_p, Structure, Union

class vector3f(Structure):
     _fields_ = [
             ("x", c_float),
             ("y", c_float),
             ("z", c_float),
         ]

class LocalizationPayload(Structure):
    _fields_ = [
            ('location', vector3f),
            ('confidence', c_float),
            ('clusterID', c_int),
        ]

class MessagePayload(Union):
    _fields_ = [
            ('localization', LocalizationPayload),
        ]

class Message(Structure):
     _fields_ = [
             ("sender", c_int),
             ("range", c_float),
             ("type", c_int),
             ("payload", MessagePayload),
         ]

class LogicalScreenGeometry(Structure):
    _fields_ = [
            ('width', c_short),
            ('height', c_short),
            ('logicalWidth', c_float),
            ('logicalHeight', c_float),
            ('x', c_short),
            ('y', c_short),
        ]

class  VisualizationWindow(Structure):
    _fields_ = [
            ('geometry', LogicalScreenGeometry),
            ('window', c_void_p),
            ('renderer', c_void_p),
            ('initalized', c_int),
        ]

