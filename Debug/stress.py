import os, sys
_, sol1, sol2, gen = sys.argv

os.system(f'g++ ./{sol1}.cpp -o {sol1}')
os.system(f'g++ ./{sol2}.cpp -o {sol2}')
os.system(f'g++ ./{gen}.cpp -o {gen}')

i = 1
while True:
    print('Test', i)
    os.system(f'./{gen} {i} > test.txt')
    v1 = os.popen(f'./{sol1} < test.txt').read()
    v2 = os.popen(f'./{sol2} < test.txt').read()
    if v1 != v2:
        print('Failed test:')
        print(open("test.txt").read())
        print(f'{sol1}: ')
        print(v1)
        print(f'{sol2}: ')
        print(v2)
        sys.exit(0)
    i += 1

