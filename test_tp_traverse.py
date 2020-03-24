import gc
from tp_traverse import tp_traverse

def test_not_tracked():
    a = 'hello'
    assert tp_traverse(a) is None

def test_tracked():
    obj = {'a': [1, 2],
           'b': [3, 4]}
    refs1 = gc.get_referents(obj)
    refs2 = tp_traverse(obj)
    assert refs1 == refs2 == ['a', [1, 2], 'b', [3, 4]]
