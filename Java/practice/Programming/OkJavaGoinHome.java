import org.opentutorials.iot.Elevator;
import org.opentutorials.iot.Security;
import org.opentutorials.iot.Lighting;

public class OkJavaGoinHome {

	public static void main(String[] args) {
		
		String id = "JAVA APT 301";
		// Elevator call
		Elevator myElevator = new Elevator(id);
		myElevator.callForUp(1);
		// Security off
		Security mySecurity = new Security(id);
		mySecurity.off();
		// Light 
		Lighting hallLamp = new Lighting(id + " / Hall Lamp");
		hallLamp.on();
		Lighting floorLamp = new Lighting(id + " / Floor Lamp");
		floorLamp.on();
		
	}

}
