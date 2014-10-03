using UnityEngine;
using System.Collections;

//ORIGINAL SCRIPT GOT FROM IJM AT UNITY ANSWERS http://answers.unity3d.com/questions/29741/mouse-look-script.html

/// MouseLook rotates the transform based on the mouse delta.
/// Minimum and Maximum values can be used to constrain the possible rotation

/// To make an FPS style character:
/// - Create a capsule.
/// - Add the MouseLook script to the capsule.
///   -> Set the mouse look to use LookX. (You want to only turn character but not tilt it)
/// - Add FPSInputController script to the capsule
///   -> A CharacterMotor and a CharacterController component will be automatically added.

/// - Create a camera. Make the camera a child of the capsule. Reset it's transform.
/// - Add a MouseLook script to the camera.
///   -> Set the mouse look to use LookY. (You want the camera to tilt up and down like a head. The character already turns.)
[AddComponentMenu("Camera-Control/Mouse Look")]
public class MouseLook : MonoBehaviour {
	
	public enum RotationAxes { MouseXAndY = 0, MouseX = 1, MouseY = 2 }
	public RotationAxes axes = RotationAxes.MouseXAndY;
	public float sensitivityX = 5F;
	public float sensitivityY = 5F;
	
	public float minimumX = -360F;
	public float maximumX = 360F;
	
	public float minimumY = -60F;
	public float maximumY = 60F;
	
	float rotationY = 0F;
	bool lockCam = true;
	public bool playedPlayerDeathSound = false;
	public AudioClip playerWhump;

	//called once per frame
	void Update ()
	{
		//lock the cursor to the center, if they press ESC then it unlocks
		if (Input.GetKey (KeyCode.Escape))
			Screen.lockCursor = false;
		else if (!lockCam)
			Screen.lockCursor = false;
		else
			Screen.lockCursor = true;
		//if you are not dead
		if (!GameObject.Find("Player").GetComponent<Script_Character>().dead) {
				//calculate rotationX and rotationY from the mouse
				if (axes == RotationAxes.MouseXAndY) {
						float rotationX = transform.localEulerAngles.y + Input.GetAxis ("Mouse X") * sensitivityX;
			
						rotationY += Input.GetAxis ("Mouse Y") * sensitivityY;
						rotationY = Mathf.Clamp (rotationY, minimumY, maximumY);
			
						transform.localEulerAngles = new Vector3 (-rotationY, rotationX, 0);
				} else if (axes == RotationAxes.MouseX) {
						transform.Rotate (0, Input.GetAxis ("Mouse X") * sensitivityX, 0);
				} else {
						rotationY += Input.GetAxis ("Mouse Y") * sensitivityY;
						rotationY = Mathf.Clamp (rotationY, minimumY, maximumY);
			
						transform.localEulerAngles = new Vector3 (-rotationY, transform.localEulerAngles.y, 0);
				}
		}
	}

	//called to display the GUI elements
	void OnGUI() {
		bool alldead = true;
		//checks to see if all the enemies died
		GameObject[] actors = GameObject.FindGameObjectsWithTag("Actor");
		foreach (GameObject a in actors) {
			if (a.name != "Player") {
				if (!a.GetComponent<EnemyAI>().dead) {
					alldead = false;
					break;
				}
			}
		}
		//are all enemies dead?
		if (alldead) {
			lockCam = false;
			//show GUI restart screen
			if (GUI.Button(new Rect(660, 230, 80, 40), "Restart")) {
				this.transform.position = new Vector3(50, 0, 50);
				Application.LoadLevel(Application.loadedLevel);
			}
			if (GUI.Button(new Rect(660, 270, 80, 40), "Next Level")) {
				this.transform.position = new Vector3(50, 0, 50);
				if (Application.loadedLevelName == "JackKnife") {
					Application.LoadLevel("JackKnife2");
				}
				else if (Application.loadedLevelName == "JackKnife2") {
					Application.LoadLevel("JackKnife");
				}
			}
			if (GUI.Button(new Rect(660, 310, 80, 40), "Quit")) {
				this.transform.position = new Vector3(50, 0, 50);
				Application.Quit();
			}
		}
		//if you died
		else if (GameObject.Find("Player").GetComponent<Script_Character>().dead) {
			lockCam = false;
			if (!playedPlayerDeathSound) {
				AudioSource.PlayClipAtPoint(playerWhump, transform.position);
				playedPlayerDeathSound = true;
			}
			//show GUI restart screen
			if (GUI.Button(new Rect(660, 230, 80, 40), "Restart")) {
				this.transform.position = new Vector3(50, 0, 50);
				Application.LoadLevel(Application.loadedLevel);
			}
			if (GUI.Button(new Rect(660, 310, 80, 40), "Quit")) {
				this.transform.position = new Vector3(50, 0, 50);
				Application.Quit();
			}
		}
		else {
			lockCam = true;
		}
	}
	
	//do not rotate
	void Start ()
	{
		// Make the rigid body not change rotation
		if (rigidbody)
			rigidbody.freezeRotation = true;
	}
}
