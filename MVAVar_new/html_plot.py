print '<!DOCTYPE html>'
print '<html>'
print '<body>'
print '<h2 align = "center" > Separation plots for ttbar and ttH </h2>'
print '<table>'
print '<tr>'
print '<td align = "center" > Variable </td>'
print '<td align = "center" > 5j, >4b </td>'
print '<td align = "center" > >6j, 3b </td>'
print '<td align = "center" > >6j,>4b </td>'
print '</tr>'
file1 = open("list.txt")
printedImg=0
for i, line in enumerate(file1):
    line = line[:-1]
    print '<tr>'
    print '<td align ="center">'+line+'</td>'
    print '<td><a href="MVAVar_new/5jex4bin/'+line+'.png"><img src ="MVAVar_new/5jex4bin/'+line+'.png" alt="'+line+'" height="300" width="300"></a></td>'
    print '<td><a href="MVAVar_new/6jin3bex/'+line+'.png"><img src ="MVAVar_new/6jin3bex/'+line+'.png" alt="'+line+'" height="300" width="300"></a></td>'
    print '<td><a href="MVAVar_new/6jin4bin/'+line+'.png"><img src ="MVAVar_new/6jin4bin/'+line+'.png" alt="'+line+'" height="300" width="300"></a></td>'
    print '</tr>'
print "</table>"
print "</body>"
print "</html>"
