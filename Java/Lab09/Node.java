package Lab09;

public class Node{       // This class contains one Object and one                       
    private Object value;  // self-referential link.       
    private Node next;           

    public Node(Object value, Node nextNode)    // The constructor inserts the
    {                                            // arguments in the new object.
         this.value = value;
         this.next = nextNode;
    }
    public Object getValue(){
    	return value;
    }
    
    public Node getNext(){
    	return next;
    }
    
    public void setValue(Object value){
    	this.value = value;
    }
    
    public void setNext(Node next){
    	this.next = next;
    }
}

