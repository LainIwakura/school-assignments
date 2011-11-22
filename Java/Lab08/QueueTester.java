package Lab08;

public class QueueTester {
	public static void main(String args[]){
		Queue<String> queueOfStrings;
		Queue<Integer> queueOfIntegers;

		queueOfStrings = new Queue<String>();
		queueOfStrings.addToBack("John");
		queueOfStrings.addToBack("Mary");
		queueOfStrings.addToBack("Robert");
		queueOfStrings.addToBack("Liz");
		while (! queueOfStrings. emptyQueue() ){
			System.out.println(queueOfStrings.removeFromFront());
		}

		queueOfIntegers = new Queue<Integer>();
		queueOfIntegers.addToBack(5);
		queueOfIntegers.addToBack(new Integer(2));
		queueOfIntegers.addToBack(9);
		queueOfIntegers.addToBack(13);
		while (! queueOfIntegers. emptyQueue() ){
			System.out.println(queueOfIntegers.removeFromFront());
		}
	}

}
