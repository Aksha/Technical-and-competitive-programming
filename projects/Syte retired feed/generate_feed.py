Readme for Syte Retired Feed:
1. There are three files used in this python script for generating Syte_Retired_Feed.xml (retailers.csv, brands.csv, test1)
2. a. retailers.csv is generated from the retailer service. It has two columns(one for retailer ID and the other for retailer name). b. brands.csv is generated from the brand service. It has two columns(one for brand ID and the other for brand name). c. test1 is generated by running the following query against any prod machine: mongo prod-mongodbcatalog-master.shopstyleops.com/catalog -u username -p password --eval 'db.products.find({ "$and": [ {"s":"Retired"}, {"ct": {"$ne": "Beauty"} }, {"ct": {"$ne": "Men"} }, {"$or": [ {"ct":"Dresses"}, {"ct":"Athletic"}, {"ct":"Shorts"}, {"ct":"Sneakers"}, {"ct":"Tops"}, {"ct":"Hats"}, {"ct":"Jeans"}, {"ct":"Sweaters"}, {"ct":"Boots"}, {"ct":"Jackets"}, {"ct":"Pumps"}, {"ct":"Sandals"}, {"ct":"Handbags"}, {"ct":"Bags"}, {"ct":"Skirts"}, {"ct":"Pants"} ] } ] }, {"p.iu":1, "n":1, "d": 1, "ct":1, "rc": 1, "bid": 1, "rid": 1, "rn":1, "co":1, "ps": 1}).sort({"lm":-1}).limit(10000000)' . It has information like the id, image_link, title, description, category tags, retailer_categories.


f3 = open('/Users/aravichandran/Desktop/all/jira tickets/CAT-1888/retailers.csv', 'r')
rd = {}
for line in f3:
    key, val = line.split(',')[0], ','.join(line.split(',')[1:])
    rd[key] = val.strip('\n')
f3.close()

import csv

brand_d = csv.reader(open('/Users/aravichandran/Desktop/all/jira tickets/CAT-1888/brands.csv'))
bd = {}   
result = {}
for row in brand_d:
    key = row[0]
    bd[key] = row[1]
    
def computeListId(d):
    res = []
    image_url = d['i']['p']['u'] if 'i' in d and 'p' in d['i'] and 'iu' in d['i']['p'] else ''
    idd = d['_id']
    if 'inv' in d:
        for invariant in d['inv']:
            fpid = invariant['fplid'] if 'fplid' in invariant else None
            c, s = None, None
            if 'c' in invariant:
                c = invariant['c']
            if 's' in invariant:
                s = invariant['s']
            color, size, url = '', '', ''
            if c!= None and c >= 0:
                color = d['co'][c]['n']
                url = d['co'][c]['p']['iu'] if 'p' in d['co'][c] else image_url
            if (s != None and s >= 0) and s < len(d['ps']):
                size = d['ps'][s]['n']
            res.append(("%d_%s" % (idd, color) if fpid == None else fpid, url))    
    else:
        res.append((idd, image_url))
    
    return res

from xml.etree.ElementTree import Element, SubElement, tostring
import xml.dom.minidom
import re
import datetime
import json
import sys
reload(sys)
sys.setdefaultencoding('utf8')


fields = {"_"}
root = Element('feed')
child = SubElement(root, 'title')
child.text = 'test'
child1 = SubElement(root, 'update')
dt = str(datetime.datetime.now())
startText = '<?xml version="1.0" encoding="UTF-8" ?><feed xmlns="http://www.w3.org/2005/Atom" xmlns:g="http://base.google.com/ns/1.0"><title>ShopStyle en_US Syte product feed</title><updated>%s</updated>'%(dt)

def addEntry(node, d, pid, image_link):
    SubElement(node, 'id').text = pid
    SubElement(node, 'image_link').text = image_link
    SubElement(node, 'title').text = d['n'] if 'n' in d else ''
    SubElement(node, 'description').text = str(d['d']) if 'd' in d else ''
    SubElement(node, 'category_tags').text = str(d['ct']) if 'ct' in d else ''
    SubElement(node, 'retailer_categories').text = str(d['rc']) if 'rc' in d else ''
    SubElement(node, 'brand').text = str(bd[int(d['bid'])]) if 'bid' in d and int(d['bid']) in bd else ''
    SubElement(node, 'custom_label_0').text = rd[str(d['rid'])] if 'rid' in d and str(d['rid']) in rd else None

with open(r'/Users/aravichandran/Desktop/all/jira tickets/CAT-1888/test1', 'r') as fin:
    with open(r'/Users/aravichandran/Desktop/all/jira tickets/CAT-1888/syte_retired_feed.xml', 'w') as fout:
        fout.write(startText)
        i = 0
        for line in fin:
            d = json.loads(re.sub(r'NumberLong\((\d+)\)', r'\1', line))
            vals = computeListId(d)
            for val in vals:
                i += 1
                pid, imUrl = val
                entryNode = Element('entry')
                if not (imUrl == None or imUrl == ''):
                    addEntry(entryNode, d, str(pid).strip('_'), imUrl)
                    fout.write(str(tostring(entryNode)).strip('"').replace('b"', '') + '\n')
                if (i %100000 == 0):
                    print(i)
                if i == 10000000:
                    break
            if i == 10000000:
                break
        fout.write('</feed>')


Python approach: 
Black and white shoes: 
Histogram: {com.shopstyle.model.CanonicalColor@3d79116:Brown=11888, com.shopstyle.model.CanonicalColor@21fe83:Gray=24149, com.shopstyle.model.CanonicalColor@4fadc09:White=282545, com.shopstyle.model.CanonicalColor@25f596:Pink=19, com.shopstyle.model.CanonicalColor@1fa47a:Blue=55738, com.shopstyle.model.CanonicalColor@8f29f3dc:Purple=484, com.shopstyle.model.CanonicalColor@3d18fc4:Beige=14347, com.shopstyle.model.CanonicalColor@3d49fdf:Black=17464, com.shopstyle.model.CanonicalColor@dffae464:NoMatch=24682, com.shopstyle.model.CanonicalColor@41ddee3:Green=698}

Blue shoes:

Histogram: {com.shopstyle.model.CanonicalColor@3d79116:Brown=144113, com.shopstyle.model.CanonicalColor@21fe83:Gray=13063, com.shopstyle.model.CanonicalColor@1fa47a:Blue=196910, com.shopstyle.model.CanonicalColor@3d49fdf:Black=2574, com.shopstyle.model.CanonicalColor@8d43124e:Orange=678, com.shopstyle.model.CanonicalColor@14071:Red=4536, com.shopstyle.model.CanonicalColor@4fadc09:White=409903, com.shopstyle.model.CanonicalColor@25f596:Pink=9194, com.shopstyle.model.CanonicalColor@3d18fc4:Beige=96130, com.shopstyle.model.CanonicalColor@8f29f3dc:Purple=51997, com.shopstyle.model.CanonicalColor@9da15094:Yellow=39, com.shopstyle.model.CanonicalColor@dffae464:NoMatch=155875, com.shopstyle.model.CanonicalColor@41ddee3:Green=350}javajjj

Java Approach:
Black and white shoes:
Histogram: {com.shopstyle.model.CanonicalColor@3d79116:Brown=145195, com.shopstyle.model.CanonicalColor@21fe83:Gray=13093, com.shopstyle.model.CanonicalColor@1fa47a:Blue=196326, com.shopstyle.model.CanonicalColor@3d49fdf:Black=2625, com.shopstyle.model.CanonicalColor@8d43124e:Orange=585, com.shopstyle.model.CanonicalColor@14071:Red=4592, com.shopstyle.model.CanonicalColor@4fadc09:White=1903978, com.shopstyle.model.CanonicalColor@25f596:Pink=8372, com.shopstyle.model.CanonicalColor@3d18fc4:Beige=96912, com.shopstyle.model.CanonicalColor@8f29f3dc:Purple=50711, com.shopstyle.model.CanonicalColor@9da15094:Yellow=38, com.shopstyle.model.CanonicalColor@dffae464:NoMatch=156219, com.shopstyle.model.CanonicalColor@41ddee3:Green=268}


3/21:
CODE CHANGED AFTER CODE REVIEW

Run it in qa-importer.. 
If it works compute timing difference between python code and Java code to understand if it dramatically slows things down. 

