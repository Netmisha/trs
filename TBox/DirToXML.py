import os
from xml.sax.saxutils import quoteattr as xml_quoteattr

def DirAsLessXML(path):
    result = '<dir name=%s>\n' % xml_quoteattr(os.path.basename(path))
    for item in os.listdir(path):
        itempath = os.path.join(path, item)
        if os.path.isdir(itempath):
            result += '\n'.join('  ' + line for line in 
                DirAsLessXML(os.path.join(path, item)).split('\n'))
        elif os.path.isfile(itempath):
            result += '  <file name=%s></file>\n' % xml_quoteattr(item)
    result += '</dir>\n'
    return result

if __name__ == '__main__':
    file_data = open('DirXMLStruct.xml','w')
    file_data.write('<?xml version="1.0"?>\n' + DirAsLessXML("PATH_TO_FOLDER"))
    file_data.close()
