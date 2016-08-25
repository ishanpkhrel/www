print '<!DOCTYPE html>'
print '<html>'
print '<body>'
print '<h2 align = "center" > WP77_StatOnly Data-MC plots </h2>'
print '<table>'
print '<tr>'
print '<td align = "center" > Variable </td>'
print '<td align = "center" > 4j,2b </td>'
print '<td align = "center" > 4j,3b </td>'
print '<td align = "center" > 4j,4b </td>'
print '<td align = "center" > 5j,2b </td>'
print '<td align = "center" > 5j,3b </td>'
print '<td align = "center" > 5j,>4b </td>'
print '<td align = "center" > 6j,>4b </td>'
print '<td align = "center" > >6j,2b </td>'
print '<td align = "center" > >6j,3b </td>'
print '<td align = "center" > >6j,>4b </td>'
print '<td align = "center" > >7j,>4b </td>'
print '</tr>'
file1 = open("WP77_StatOnly/files.txt")
printedImg=0
for i, line in enumerate(file1):
    line = line[:-1]
    name=line.split('_')
    if(printedImg == 0):
        print '<tr>'
	print '<td>'+name[0]+'_'+name[1]+'</td>'
    print '<td><a href="'+line+'"><img src ="'+line+'" alt="'+line+'" height="150" width="150"></a></td>'
    printedImg = printedImg+1
#      if(printedImg == 11):
    if line.endswith('ge7jge4b.png'):
        print '</tr>'
        printedImg = 0
print "</table>"
print "</body>"
print "</html>"
