def singleton(class_):
    instances = {}
    def getinstance(*args, **kwargs):
        if class_ not in instances:
            instances[class_] = class_(*args, **kwargs)
        return instances[class_]
    return getinstance

@singleton
class Settings():
    def __init__(self,g):
        self._node_id = 0
        self._nb = 64
        self._sampling_freq=44100.0
        self._g = g

    @property
    def g(self):
        return self._g
    
    def new_node_id(self):
        r = self._node_id 
        self._node_id = self._node_id + 1
        return r

    @property
    def nb(self):
        return self._nb

    @property
    def sampling_freq(self):
        return self._sampling_freq
    
    
    