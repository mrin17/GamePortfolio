using UnityEngine;
using System.Collections;

public class shootDemo : MonoBehaviour {
	
	public Rigidbody projectile;
	
	public GameObject bulletTrailPrefab;
	
	public GameObject owner;
	
	//Sounds
	public AudioClip shotClip;
	public AudioClip meleeClip;
	public AudioClip whoosh;
	
	//Score
	public GUIText pScore;
	public int score = 0;
	
	//Ammo
	public GUIText pAmmo;
	public int ammo = 3;
	public int maxAmmo;

	public GUIText distanceToClosestEnemy;

	public int meleeing = 0; // number of frames left of your melee attack
	
	
	// Use this for initialization
	void Start () {
		maxAmmo = ammo;
	}
	
	//displays the GUI elements
	void OnGUI() {
		pScore.text = "Enemies Defeated: " + score + "/7";
		pAmmo.text = ammo + "/" + maxAmmo;
		//distance code, calculates the distance to the closest enemy
		int dist = 0;
		int currentdist = 0;
		GameObject[] actors = GameObject.FindGameObjectsWithTag("Actor");
		foreach (GameObject a in actors) {
			if (a.name != "Player") {
				if (!a.GetComponent<EnemyAI>().dead) {
					currentdist = (int) Vector3.Distance(transform.position, a.transform.position);
					if (dist == 0 || currentdist < dist) {
						dist = currentdist;
					}
				}
			}
		}
		distanceToClosestEnemy.text = "Distance to Closest Enemy: " + dist;
	}
	
	// FROM:
	// http://answers.unity3d.com/questions/21174/create-cylinder-primitive-between-2-endpoints.html
	//draws a cylinder between 2 points, used to sisplay the gun trail
	void CreateCylinderBetweenPoints(Vector3 start, Vector3 end, float width)
	{
		Vector3 offset = end - start;
		Vector3 scale = new Vector3(width, offset.magnitude / 2.0f, width);
		Vector3 position = start + (offset / 2.0f);
		
		GameObject cylinder = (GameObject)(Instantiate(bulletTrailPrefab, position, Quaternion.identity));
		cylinder.transform.up = offset;
		cylinder.transform.localScale = scale;
	}
	
	// Update is called once per frame
	void Update () {
		if (meleeing > 0) {meleeing--;}

		if (!GameObject.Find("Player").GetComponent<Script_Character>().dead) {
			this.liveUpdate();
		}
	}

	//calculates shooting and melee attacks
	void liveUpdate() {
		//shoot
		if (Input.GetButtonDown("Fire1") && !(this.ammo == 0)) {
			if (this.meleeing == 0) {this.shoot();}
		}
		//melee 
		else if (Input.GetButtonDown("Fire2")) {
			this.melee();
		}
	}

	//makes the character shoot a bullet
	void shoot() {
		
		this.ammo--;
		
		AudioSource.PlayClipAtPoint(shotClip, transform.position);
		
		Vector3 gunPosition = transform.parent.gameObject.transform.position;
		
		//raycast a red cylinder from your gun to the target
		int RAYCAST_LENGTH = 100;
		
		int x = Screen.width / 2;
		int y = Screen.height / 2;
		Ray ray = Camera.main.ScreenPointToRay(new Vector3(x, y, 0));
		ray.origin = gunPosition;
		
		Debug.DrawRay(ray.origin, ray.direction * RAYCAST_LENGTH, Color.yellow);

		// if you hit someone, you trade places and increase your score
		tradePlacesAndScore (ray, RAYCAST_LENGTH);

		// draw bullet path
		Vector3 startPoint = ray.origin;
		Vector3 endPoint = startPoint + (ray.direction * RAYCAST_LENGTH);

		RaycastHit hit;
		if (Physics.Raycast(ray, out hit, RAYCAST_LENGTH)) {
			endPoint = hit.point;
		}
		//draws the cylinder
		CreateCylinderBetweenPoints(startPoint, endPoint, 0.1f);
	}

	//makes the character use its melee weapon
	void melee() {
		if (meleeing == 0) {
			AudioSource.PlayClipAtPoint(meleeClip, transform.position);

			// get short-range melee ray
			Vector3 gunPosition = transform.parent.gameObject.transform.position;
			int RAYCAST_LENGTH = 2;
			
			int x = Screen.width / 2;
			int y = Screen.height / 2;
			Ray ray = Camera.main.ScreenPointToRay(new Vector3(x, y, 0));
			ray.origin = gunPosition;
			
			Debug.DrawRay(ray.origin, ray.direction * RAYCAST_LENGTH, Color.red);
			//if the melee ray hit someone, trade places and increase score
			tradePlacesAndScore (ray, RAYCAST_LENGTH);
			//animate the gun
			this.transform.parent.gameObject.animation.Play ("meleeAnimation");
			
			this.meleeing = 20;
		}
	}

	//calculates if the ray hit an enemy, and if so, you and the enemy trade places and your score is increased
	void tradePlacesAndScore(Ray ray, int raycastLength) {

		RaycastHit hit;
		//if the ray hit something
		if (Physics.Raycast(ray, out hit, raycastLength)) {
			Debug.Log(hit.collider.gameObject.tag);
			//if the thing it hit was an actor and its not dead
			if ((hit.collider.gameObject.tag == "Actor") && (!hit.collider.gameObject.GetComponent<EnemyAI>().dead)) {
				//increment score
				score += 1;
				
				GameObject gun = transform.parent.gameObject;
				GameObject cam = gun.transform.parent.gameObject;
				GameObject owner = cam.transform.parent.gameObject;

				Vector3 ourPosition = owner.transform.position;
				Vector3 theirPosition = hit.collider.gameObject.transform.position;
				AudioSource.PlayClipAtPoint(whoosh, theirPosition);
				
				// trade places!
				owner.transform.position = theirPosition;
				hit.collider.gameObject.transform.position = ourPosition;
				
				// KILL HIM
				hit.collider.gameObject.GetComponent<EnemyAI>().dead = true;
				
				Debug.Log (hit.collider.gameObject.layer);
			}
		}
	}
}
