# I will use Euclidean algorithm to calculate GCD and LCM
# https://en.wikipedia.org/wiki/Euclidean_algorithm


def GCD(a,b):  # by Euclidean algorithm  to calculate GCD I should calculate the remainder of a/b (a>b)
    if a%b ==0:   # if the remainder of a/b is zero b is GCD of original a&b
        return b
    else:   # else should calculate b and the remainder of a/b's GCD to calculate the GCD of original a&b
        return GCD(b,a%b)   # Recursion function


def LCM(a,b):     # LCM is the "Least Common Multiple" so GCD x each numbers remainder that comes from num/GCD is LCM
    return int(a*b/GCD(a,b))


input_numbers = list(map(int, input("Please Enter two integers: ").split(' '))) #input 2 numbers with spacing between numbers
# split by spacing and make string list to int list by using map and list method
input_numbers.sort(reverse=True) # sort the list by descending order
print("LCM : {} GCD : {}".format(LCM(input_numbers[0], input_numbers[1]), GCD(input_numbers[0], input_numbers[1])))
