#! /usr/bin/env python3


import sys

if len(sys.argv) < 2:
    print("No File")
    sys.exit(0)


sallocs = {}
mallocs = []
mallocs_ends = []
for lines in open(sys.argv[1]):
    if "SAlloc" in lines:
        lines = lines.replace("\n", "")
        lines = lines.split()
        if lines[1] in sallocs:
            print("Error1 here: " + str(lines))
            sys.exit(0)

        iaddr = int(lines[1], 0)
        for i in range(0, len(mallocs)):
            if iaddr >= mallocs[i] and iaddr < mallocs_ends[i]:
                print("Error2 here: " + str(lines))
        sallocs[lines[1]] = "in"
    elif "MAlloc" in lines:
        lines = lines.replace("\n", "")
        lines = lines.split()
        lines[0] = lines[0].replace("MAlloc(", "")
        lines[0] = lines[0].replace("):", "")


        lsize = int(lines[0])
        iaddr = int(lines[1], 0)
        
        if lines[1] in sallocs:
            print("Error3 here: " + str(lines))
            sys.exit(0)
        
        for i in range(0, len(mallocs)):
            if iaddr >= mallocs[i] and iaddr < mallocs_ends[i]:
                print("Error4 here: " + str(lines))
                
        mallocs.append(iaddr)
        mallocs_ends.append(iaddr + lsize)
    elif "Free" in lines:
        lines = lines.replace("\n", "")
        lines = lines.split(" ")
        faddr = lines[len(lines) - 1]

        if faddr in sallocs:
            del sallocs[faddr]

        iaddr = int(faddr, 0)

        good = 0
        for i in range(0, len(mallocs)):
            if iaddr == mallocs[i]:
                mallocs.remove(mallocs[i])
                mallocs_ends.remove(mallocs_ends[i])
                good = 1
                break
        if good == 0:
            print("Error5 here: " + str(lines))
            
    
        

        
