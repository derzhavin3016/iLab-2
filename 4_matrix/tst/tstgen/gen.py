#!/usr/bin/env python3
import numpy as np
import argparse

def main():
    parser = argparse.ArgumentParser(description='Genrator of matrix for test')
    parser.add_argument('size', metavar='SIZE', type=int, help='size of a matrix')
    parser.add_argument('fr', metavar='FROM', type=int, help='start value for generate numbers')
    parser.add_argument('to', metavar='TO', type=int, help='end value for generate numbers')

    args = parser.parse_args()

    if args.size <= 0:
        print('Incorrect size: ' + str(args.size) + '\nTry again')
        return

    matr = np.random.randint(args.fr, args.to, (args.size, args.size))
    det = np.linalg.det(matr)

    print(args.size)
    for i in range(args.size):
        for j in range(args.size):
            print(matr[i][j], end=' ')
        print()
    print('Det = ' + str(det))


if __name__ == '__main__':
    main()