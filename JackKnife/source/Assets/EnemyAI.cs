using UnityEngine;
using System.Collections;

//ORIGINAL CODE FROM: https://unity3d.com/learn/tutorials/projects/stealth/enemy-ai

public class EnemyAI : MonoBehaviour
{
	public float patrolSpeed = 2f;                          // The nav mesh agent's speed when patrolling.
	public float chaseSpeed = 5f;                           // The nav mesh agent's speed when chasing.
	public float chaseWaitTime = 5f;                        // The amount of time to wait when the last sighting is reached.
	public float patrolWaitTime = 1f;                       // The amount of time to wait when the patrol way point is reached.
	public Transform[] patrolWayPoints;                     // An array of transforms for the patrol route.
	
	public GameObject bulletTrailPrefab;
	
	private EnemySight enemySight;                          // Reference to the EnemySight script.
	private NavMeshAgent nav;                               // Reference to the nav mesh agent.
	private Transform m_Player;                               // Reference to the player's transform.
	private float chaseTimer;                               // A timer for the chaseWaitTime.
	private float patrolTimer;                              // A timer for the patrolWaitTime.
	private int wayPointIndex;                              // A counter for the way point array.
	
	public AudioClip shotClip;
	public int shotWait = 0;
	public bool dead = false;
	
	//called once when created
	void Awake ()
	{
		// Setting up the references.
		enemySight = GetComponent<EnemySight>();
		nav = GetComponent<NavMeshAgent>();
	}
	
	//called once per frame
	void Update ()
	{
		if (!dead) {
			//		// If the player is in sight and is alive...
			if(enemySight.playerInSight)
				// ... shoot.
				Shooting();
			
			// Otherwise...
			else
				// ... patrol.
				Patrolling();
			
			if (shotWait > 0) {
				shotWait--;
			}
		} else {
			// X.X
			nav.Stop();
			transform.eulerAngles = new Vector3(90, 0, 0);
			Destroy(this.gameObject);
		}
	}
	
	// FROM:
	// http://answers.unity3d.com/questions/21174/create-cylinder-primitive-between-2-endpoints.html
	//creates a cylinder between 2 points, used for gun trails
	void CreateCylinderBetweenPoints(Vector3 start, Vector3 end, float width)
	{
		Vector3 offset = end - start;
		Vector3 scale = new Vector3(width, offset.magnitude / 2.0f, width);
		Vector3 position = start + (offset / 2.0f);
		
		GameObject cylinder = (GameObject)(Instantiate(bulletTrailPrefab, position, Quaternion.identity));
		cylinder.transform.up = offset;
		cylinder.transform.localScale = scale;
	}
	
	//called when the enemy is shooting
	void Shooting ()
	{
		// Stop the enemy where it is.
		nav.Stop();
		if (shotWait == 0) {
			
			GameObject player = GameObject.Find("Player");
			
			AudioSource.PlayClipAtPoint(shotClip, transform.position);
			shotWait = 50;
			//DO SOME RANDOM RAY TRACING!!!!!
			
			Vector3 startPos = transform.FindChild("GunE").gameObject.transform.FindChild("GunEEnd").transform.position;
			
			float dist = Vector3.Distance(player.transform.position, startPos);
			
			float inaccuracy = dist/10f;
			
			float playerX = player.transform.position.x;
			float playerY = player.transform.position.y;
			float playerZ = player.transform.position.z;
			
			float shotX = Random.Range (-inaccuracy, inaccuracy) + playerX;
			float shotY = Random.Range (-inaccuracy, inaccuracy) + playerY;
			float shotZ = Random.Range (-inaccuracy, inaccuracy) + playerZ;
			
			Vector3 shotPos = new Vector3 (shotX, shotY, shotZ);
			Vector3 cylinderEnd = shotPos;
			
			int RAYCAST_LENGTH = 100;
			//enemy shoots at a random direction close to you
			RaycastHit hit;
			if (Physics.Raycast (startPos, (shotPos - startPos), out hit)) {
				Debug.Log("HIT " + hit.collider.gameObject + " " + hit.point);
				if (hit.collider.gameObject == player) {
					player.GetComponent<Script_Character>().dead = true;
				}
				cylinderEnd = hit.point;
			}
			
			CreateCylinderBetweenPoints(startPos, cylinderEnd, 0.1f);
		}
	}
	
	//used when the enemy is patrolling (and not shooting), it just follows the given path
	void Patrolling ()
	{
		// Set an appropriate speed for the NavMeshAgent.
		nav.speed = patrolSpeed;
		
		// If near the next waypoint or there is no destination...
		if(nav.remainingDistance < nav.stoppingDistance)
		{
			// ... increment the timer.
			patrolTimer += Time.deltaTime;
			
			// If the timer exceeds the wait time...
			if(patrolTimer >= patrolWaitTime)
			{
				// ... increment the wayPointIndex.
				if(wayPointIndex == patrolWayPoints.Length - 1)
					wayPointIndex = 0;
				else
					wayPointIndex++;
				
				// Reset the timer.
				patrolTimer = 0;
			}
		}
		else
			// If not near a destination, reset the timer.
			patrolTimer = 0;
		
		// Set the destination to the patrolWayPoint.
		nav.destination = patrolWayPoints[wayPointIndex].position;
	}
}