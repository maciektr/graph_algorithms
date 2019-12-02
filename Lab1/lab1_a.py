from dimacs import loadWeightedGraph

def find(k, FU):
    i=k
    while FU[i][0]!=i:
        i = FU[i][0]
    FU[k][0] = i
    return i

def union(x,y, FU):
    x = find(x, FU)
    y = find(y, FU)
    if FU[x][1] < FU[y][1]:
        FU[x][0] = y
    else:
        if FU[x][1]==FU[y][1]:
            FU[y][1]+=1
        FU[y][0] = x

def solve(test_path):
    (V,L) = loadWeightedGraph(test_path)
    FU = [[i,0] for i in range(V+1)]

    s = 1
    t = 2
    L = sorted(L,key=lambda x:-x[2])
    res = L[0][2]

    for edge in L:
        union(edge[0],edge[1], FU)
        res = min(res,edge[2])
        if find(s, FU) == find(t, FU):
            break
    return res