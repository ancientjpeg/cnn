from PIL import Image
from pathlib import Path
import numpy as np
from random import random
import json

from numpy.core.fromnumeric import size


class CNNImager:
    def __init__(self, size: tuple = (28, 28), mode: str = 'L') -> None:
        self.size: tuple = size
        self.mode: str = mode

    def get_bytes_from_file(self, path: Path or str):
        with open(path, 'rb') as f:
            d = f.read()
        return d

    def write_bytes_to_image(
        self, path: Path or str, b: bytes = None, format: str = 'PNG'
    ):
        if not b:
            b = self.dat
        im = Image.frombytes(self.mode, self.size, b)
        im.save(path, format=format)

    def write_array_to_image(self, path: Path or str, a: np.array, format: str = 'PNG'):
        im = Image.fromarray(a)
        im.save(path, format=format)


if __name__ == "__main__":

    imager = CNNImager()
    d = imager.get_bytes_from_file('test/output.dat')
    imager.write_bytes_to_image('out.PNG', d)
