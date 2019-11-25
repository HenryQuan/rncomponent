import sys
import os.path

filename = sys.argv[1]
if os.path.isfile(filename):
    with open(filename) as f:
        with open('{}.out'.format(filename),'w') as output:
            # read and write at the same time
            for line in f.readlines():
                output.write('fprintf(replace_this, "{}");\n'.format(line.rstrip().replace('	', '    ')))
        
else:
    print('{} does not exists'.format(filename))