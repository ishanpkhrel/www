import os

fp = open("folder.txt")
for i, line in enumerate(fp):
  line = line[:-1]
  cmd='rm '+str(line)+'/*png'
#  cmd+='\n'
#  cmd+='rm -r '+str(line)+'/user*'
  os.popen(cmd)    
  print cmd
