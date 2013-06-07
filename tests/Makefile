default: gtest/Makefile gtest/lib/libgtest.a
	make -C unit/

gtest/Makefile:
	cd gtest/ && ./configure && cd ..

gtest/lib/libgtest.a: gtest/src/gtest-all.o
	cd gtest/src && ar q libgtest.a gtest-all.o && \
		mv libgtest.a ../lib && cd ../..

gtest/src/gtest-all.o: gtest/Makefile
	make -C gtest

clean:
	-$(REMOVE) *.pyc
	-make -C gtest/ clean
	-rm gtest/lib/libgtest.a
	make -C functional/ clean
	make -C unit/ clean

distclean: clean
	-make -C gtest/ distclean

.PHONY : clean gtest
