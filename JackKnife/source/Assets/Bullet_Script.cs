using UnityEngine;
using System.Collections;

public class Bullet_Script : MonoBehaviour {
	
	public GameObject who_shot_it;
	int speed = 5;
	Vector3 position;
	Vector3 direction;
	
	// Use this for initialization
	void Start () {
		//set direction, who_shot_it, and position
		//this should be done by the player
	}
	
	//when the bullet hits something
	void OnTriggerEnter(Collider c) {
		//what are you doing, you shot yourself
		if (c.gameObject == who_shot_it) {
		}
		//you shot someone, switch places of Enemy and who_shot_it
		else if (c.gameObject.name == "Enemy" || c.gameObject.name == "Character") {
			Vector3 temp = c.gameObject.transform.position;
			c.gameObject.transform.position = who_shot_it.transform.position;
			who_shot_it.transform.position = temp;
		}
		//destroy the object you hit
		Destroy (gameObject, 0f);
	}
	
	// Update is called once per frame
	void Update () {
		// if y > 10 then the bullet disappears
		if (this.transform.position.y > 10) {
			Destroy (gameObject, 0f);
		}
		//move the bullet
		else {
			Vector3 temp = transform.position;
			temp.x += direction.x*speed;
			temp.y += direction.y*speed;
			temp.z += direction.z*speed;
			transform.position = temp;
		}
	}
}
