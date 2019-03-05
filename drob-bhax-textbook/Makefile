all:	clean fdl

fdl:	clean validate_drob-bhax-textbook_fdl_hu drob-bhax-textbook_fdl.pdf
	
drob-bhax-textbook_fdl.pdf: drob-bhax-textbook-fdl.xml drob-bhax-textbook.xls
	dblatex drob-bhax-textbook-fdl.xml -p drob-bhax-textbook.xls
	
.PHONY: validate_drob-bhax-textbook_fdl_hu
validate_drob-bhax-textbook_fdl_hu:
	xmllint --xinclude drob-bhax-textbook-fdl.xml --output output.xml
	xmllint --relaxng http://docbook.org/xml/5.0/rng/docbookxi.rng output.xml --noout
	rm -f output.xml	
	
.PHONY: clean
clean:
	rm -f drob-bhax-textbook-fdl.pdf
