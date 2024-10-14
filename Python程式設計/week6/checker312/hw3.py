import hw_decorator

def pretty(o_fun):
    def n_fun(*arg, **kwargs):
        return ('$'+ o_fun(*arg, **kwargs) +'$')
    return n_fun


@pretty
def f1():  
  return 'f1'

print(f1())

hw_decorator.checker(pretty)