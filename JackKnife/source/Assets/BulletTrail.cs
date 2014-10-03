using UnityEngine;
using System.Collections;

public class BulletTrail : MonoBehaviour {

	public int life = 10;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		//bullet lifetime
		if (life <= 0) {
			Destroy(this.gameObject);
		} else {
			life--;
		}
	}
}
