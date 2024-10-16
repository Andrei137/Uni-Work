def first_index(arr, left, right, k):
    if left <= right:
        mid = left + ((right - left) >> 1)
        # primul element din arr egal cu k
        if (mid == 0 or k > arr[mid - 1]) and arr[mid] == k:
            return mid
        # k este mai mare decat elementul din mijloc -> cautare in dreapta
        elif k > arr[mid]:
            return first_index(arr, mid + 1, right, k)
        # k este mai mic decat elementul din mijloc -> cautare in stanga
        return first_index(arr, left, mid - 1, k)
    return -1


def last_index(arr, left, right, k):
    if left <= right:
        mid = left + ((right - left) >> 1)
        # ultimul element din arr egal cu k
        if (mid == len(arr) - 1 or k < arr[mid + 1]) and arr[mid] == k:
            return mid
        # k este mai mare decat elementul din mijloc -> cautare in dreapta
        elif k > arr[mid]:
            return last_index(arr, mid + 1, right, k)
        # k este mai mic decat elementul din mijloc -> cautare in stanga
        return last_index(arr, left, mid - 1, k)
    return -1


arr = [int(x) for x in input().split()]
n = len(arr)
k = int(input())
i = first_index(arr, 0, n - 1, k)
if i == -1:
    print("Not found")
else:
    # numar aparitii = last_index - first_index + 1
    print(last_index(arr, 0, n - 1, k) - i + 1)
