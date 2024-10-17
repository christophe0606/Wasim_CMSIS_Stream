bpm = 66 
f = 44100 

def joinit(iterable, delimiter):
    it = iter(iterable)
    yield next(it)
    for x in it:
        yield delimiter
        yield x

def simpl(l):
    if len(l)>=2:
        if (l[0]=="") and (l[1]==""):
            l = l[1:]
        if (l[-1]=="") and (l[-2]==""):
            l = l[:-1]
    return(l)

#a="33 _33 36_33_ 36_33_ 28 _28 31_28_ 31"
#print(compounds)

def genEvent(a):
    notes=a.split()
    compounds=[simpl(list(joinit(x.split('_'),""))) for x in notes]

    compounds_num = len(compounds)
    for i,c in enumerate(compounds):
        relative_time_base = 1.0*i / compounds_num
        elements_n = len(c)
    
        for j,element in enumerate(c):
            relative_time_sub = 1.0 / compounds_num * j / elements_n
            time = relative_time_sub + relative_time_base 

            if len(element)!=0:
                yield("{"+f"{time},{int(element)}"+ "}")

def seqVals(a):
    r = "{"+",".join(list(genEvent(a)))+"}"
    return(r)

#print(seqVals(a))
