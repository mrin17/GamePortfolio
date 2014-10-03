using UnityEngine;
using System.Collections;

//ORIGINAL SCRIPT FROM UNITY DOCS http://docs.unity3d.com/Documentation/ScriptReference/CharacterController.Move.html

//TERRAIN CREDITS - grass and walls provided by Unity
//CRATE CREDITS - https://www.assetstore.unity3d.com/#/content/4428 publisher is Yugi Nagata
//METAL WALL CREDITS - https://www.assetstore.unity3d.com/#/content/12949 publishers are Nobiax/Yughues

public class Script_Character : MonoBehaviour {

	public float speed = 6.0F;
	public float jumpSpeed = 8.0F;
	public float gravity = 20.0F;
	private Vector3 moveDirection = Vector3.zero;
	public float rotx = 0;
	public float roty = 0;
	public Vector3 camrotation = Vector3.zero;
	public Rigidbody bulletPrefab;
	public GameObject gunPrefab;
	public float bulletSpeed = 1.0f;
	public bool dead = false;

	// Use this for initialization
	void Start () {

	}
	//called once per frame
	void Update() {
		//if youre not dead
		if (!dead) {
			CharacterController controller = GetComponent<CharacterController> ();
			//if you are grounded, then you can jump and more freely change your speed
			if (controller.isGrounded) {
					moveDirection = new Vector3 (Input.GetAxis ("Horizontal"), 0, Input.GetAxis ("Vertical"));
					moveDirection = transform.TransformDirection (moveDirection);
					moveDirection *= speed;
					if (Input.GetButton ("Jump"))
							moveDirection.y = jumpSpeed;

			}
			controller.Move (moveDirection * Time.deltaTime);
		}
		//if youre dead kill the player tracker and flip you on your side
		else {
			transform.eulerAngles = new Vector3(-90, 0, 0);
			Destroy(GameObject.Find("Player_Tracker"));
		}
		//account for gravity
		moveDirection.y -= gravity * Time.deltaTime;
	}

}
