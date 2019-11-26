CXXFLAGS = -std=c++11 -Wall -Werror

all: cfs_sched

map_tester: map_tester.cc
	$(CXX) -o $@ $^

multimap_tester: multimap_tester.cc
	$(CXX) -o $@ $^

cfs_sched: cfs_sched.cc
	$(CXX) -o $@ $^

execs = map_tester multimap_tester cfs_sched

clean:
	rm -f $(execs)
