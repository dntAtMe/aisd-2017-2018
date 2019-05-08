JFLAGS= -g 

JC= javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES1 = \
    	Main.java \
    	Sort.java \
	SortFactory.java \
	InsertionSort.java \
	MergeSort.java \
	QuickSort.java \
	DPQuickSort.java \
	ComparingOrder.java \
	ComparingOrderFactory.java \
	IncComparingOrder.java \
	DecComparingOrder.java \

default: classes


classes: $(CLASSES1:.java=.class)

clean:
	$(RM) *.class  
