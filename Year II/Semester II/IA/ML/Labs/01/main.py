import numpy as np
import matplotlib.pyplot as plt
from skimage import io

# a
images = np.empty((9, 400, 600))
for i in range(9):
    file_path = f"images/car_{i}.npy"
    image = np.load(file_path)
    images[i] = image

# b
print(np.sum(images))

# c
maxx = -1
max_idx = -1
for i in range(9):
    S = np.sum(images[i])
    if S > maxx:
        maxx = S
        max_idx = i
    print(f"Sum of the pixels in image {i}: {S}")

# d
print(f"Suma maxima este {maxx}, gasita la indexul {max_idx}")

# e
mean_image = np.mean(images, axis=0)
io.imshow(mean_image.astype(np.uint8))
io.show()

# f
standard_deviation = np.std(images)
print(standard_deviation)

# g
for i in range(9):
    images[i] = (images[i] - mean_image) / standard_deviation
    io.imshow(images[i].astype(np.uint8))
    io.show()

# h
images = images[:, 200:301, 280:401]
for i in range(9):
    io.imshow(images[i].astype(np.uint8))
    io.show()
