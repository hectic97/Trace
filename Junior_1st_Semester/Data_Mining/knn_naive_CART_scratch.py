# 1
# The types of train,test,cl and k are list
# ex) train = [[1,2],[4,5],[7,4],[0,0]], cl = [0,1,1,2]
def myknn(train, test, cl, k, method):
    predicted_class = []
    for te in test:
        ds = []
        for tr in train:
            ds.append(sum([(x - y) ** 2 for x, y in zip(tr, te)]) ** 0.5)
        nearest_ds = sorted(ds)[:k]  # 같은 거리의 데이터들에대해 index 순으로 처리하였습니다.
        nearest_index = [ds.index(x) for x in nearest_ds]
        nearest_cl = [cl[x] for x in nearest_index]
        if method == 1:
            nearest_dict = {}
            for c in nearest_cl:
                if c not in nearest_dict:
                    nearest_dict[c] = 1
                else:
                    nearest_dict[c] += 1

            max_cnt = 0
            for label, cnt in nearest_dict.items():
                if cnt >= max_cnt:
                    max_cnt = cnt
                    max_cl = label

        elif method == 2:
            weight = []
            for x in nearest_ds:
                if x != 0:
                    weight.append(1 / x)
                else:
                    weight.append(0)
            nearest_dict = {}
            for c, w in zip(nearest_cl, weight):
                if c not in nearest_dict:
                    nearest_dict[c] = w
                else:
                    nearest_dict[c] += w
            max_wgt = 0

            for label, wgt in nearest_dict.items():
                if wgt >= max_wgt:
                    max_wgt = wgt
                    max_cl = label

        predicted_class.append(max_cl)
    return predicted_class

# 2
# train=[[0,0],[0,0],[0,1],[0,1],[0,0],[1,0],[1,0],[1,0],[1,1],[1,0]]
# cl = ['A','B','B','B','A','A','B','B','A','A']
# homework 1의 2번 문제를 예시로 실행하였습니다. R에서의 factor를 list로 구현하였습니다.
# cond_prob 의 class 와 X의 순서는 train 데이터에서 먼저 등장하는 순서대로 구현하였습니다.

def myNaiveBayes(train, cl):
    cl_dict = {}
    for c in cl:
        if c not in cl_dict:
            cl_dict[c] = 1
        else:
            cl_dict[c] += 1
    unique_cl = [x for x in cl_dict.keys()]
    priors = [x / len(cl) for x in cl_dict.values()]
    cond_prob = []
    [x.append(y) for x, y in zip(train, cl)]
    train_by_cl = []
    for uc in unique_cl:
        same_cl_lst = []
        for m in train:
            if m[-1] == uc:
                same_cl_lst.append(m)
        train_by_cl.append(same_cl_lst)
    nx = len(train[0]) - 1
    for feature in range(nx):
        f_lst = [x[feature] for x in train]
        unique_x = []
        for x in f_lst:
            if x not in unique_x:
                unique_x.append(x)

        feature_cond_prob = []
        for i, label in enumerate(unique_cl):
            label_m = len(train_by_cl[i])
            label_cond_prob = []
            for x in unique_x:
                count = 0
                for k in train_by_cl[i]:
                    if k[feature] == x:
                        count += 1
                label_cond_prob.append((count+1)/(label_m+len(cl_dict)))
            feature_cond_prob.append(label_cond_prob)
        cond_prob.append(feature_cond_prob)

    return list((priors, cond_prob))


#3
def myInfoEntropy(cl_1, cl_2):
    import math
    uq_cl_1 = []
    uq_cl_2 = []
    for y in cl_1:
        if y not in uq_cl_1:
            uq_cl_1.append(y)
    for y in cl_2:
        if y not in uq_cl_2:
            uq_cl_2.append(y)
    E_c1 = 0
    E_c2 = 0
    for c in uq_cl_1:
        E_c1 += cl_1.count(c) / len(cl_1) * math.log(cl_1.count(c) / len(cl_1), 2)
    for c in uq_cl_2:
        E_c2 += cl_2.count(c) / len(cl_2) * math.log(cl_2.count(c) / len(cl_2), 2)
    E_c1 *= -1
    E_c2 *= -1
    sum_ent = len(cl_1) / (len(cl_1) + len(cl_2)) * E_c1 + len(cl_2) / (len(cl_1) + len(cl_2)) * E_c2

    return sum_ent

# myInfoEntropy return 값이 최소가 되도록 데이터를 나눕니다.
# dt=[[1,4],[2,6],[2,5],[2,4],[2,3],[3,6],[4,6],[4,5],[4,4],[5,4]]
# cl=[1,1,1,1,1,2,2,2,1,1]
# list를 input으로 받습니다.

def mySplit(dt, cl):
    m = len(cl)
    unique_cl = {}
    for y in unique_cl:
        if y not in unique_cl:
            unique_cl[y] = 1
        else:
            unique_cl[y] += 1

    def combination(x):
        if len(x) == 0:
            return [[]]
        cb = []
        for c in combination(x[1:]):
            cb += [c, c + [x[0]]]
        return cb

    comb_lst = combination(list(range(m)))
    del comb_lst[0]
    min_ent = 1

    for comb in comb_lst:
        idx_lst_1 = list(range(m))
        idx_lst_2 = comb
        label_lst_1 = [cl[x] for x in comb]
        for x in comb:
            idx_lst_1.remove(x)
        label_lst_2 = [cl[x] for x in idx_lst_2]
        if myInfoEntropy(label_lst_1, label_lst_2) <= min_ent:
            min_ent = myInfoEntropy(label_lst_1, label_lst_2)
            min_index = idx_lst_1, idx_lst_2

    dt_left = [dt[x] for x in min_index[0]]
    dt_right = [dt[x] for x in min_index[1]]
    cl_left = [cl[x] for x in min_index[0]]
    cl_right = [cl[x] for x in min_index[1]]
    t1 = list((dt_left, cl_left))
    t2 = list((dt_right, cl_right))

    return list((t1, t2))


##### TEST CASE #####

"""
train=[[0.5,1.5],[1,2],[2,1.5],[2.2,3],[2.5,2.7],[3,3],[7,11]]
label = [0,0,0,1,1,1,2]
test=[[0,0],[2.2,3.1],[4,4],[7,10]]
print(myknn(train,test,label,2,2))

train=[[0,0],[0,0],[0,1],[0,1],[0,0],[1,0],[1,0],[1,0],[1,1],[1,0]]
cl = ['A','B','B','B','A','A','B','B','A','A']
print(myNaiveBayes(train,cl))

dt=[[1,4],[2,6],[2,5],[2,4],[2,3],[3,6],[4,6],[4,5],[4,4],[5,4]]
cl=[1,1,1,1,1,2,2,2,1,1]
print(mySplit(dt,cl))
"""