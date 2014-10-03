using UnityEngine;
using System.Collections;

//ORIGINAL CODE FROM: https://unity3d.com/learn/tutorials/projects/stealth/enemy-sight

public class EnemySight : MonoBehaviour
{
	public float fieldOfViewAngle = 110f;           // Number of degrees, centred on forward, for the enemy see.
	public bool playerInSight = false;                      // Whether or not the player is currently sighted.
	public Vector3 personalLastSighting;            // Last place this enemy spotted the player.
	
	
	private NavMeshAgent nav;                       // Reference to the NavMeshAgent component.
	private SphereCollider col;                     // Reference to the sphere collider trigger component.
	private CapsuleCollider cap;
	private Animator anim;                          // Reference to the Animator.
	private GameObject player;                      // Reference to the player.
	private Animator playerAnim;                    // Reference to the player's animator component.
	private Vector3 previousSighting;               // Where the player was sighted last frame.

	//called once when created
	void Awake ()
	{
		// Setting up the references.
		nav = GetComponent<NavMeshAgent>();
		cap = GetComponent<CapsuleCollider> ();
		col = GetComponent<SphereCollider>();
		col.gameObject.layer = 1 << 4;
		anim = GetComponent<Animator>();
		player = GameObject.Find("Player");
		playerAnim = player.GetComponent<Animator>();
	
	}
	
	//called once per frame
	void Update ()
	{
		// Create a vector from the enemy to the player and store the angle between it and forward.

		Vector3 direction = GameObject.Find("Player").transform.position - transform.position;
		float angle = Vector3.Angle(direction, transform.forward);
	
		// If the angle between forward and where the player is, is less than half the angle of view...
		if(angle < fieldOfViewAngle * 0.5f)
		{
			RaycastHit hit;
			
			// ... and if a raycast towards the player hits something...
			if(Physics.Raycast(transform.position, direction.normalized, out hit, col.radius))
			{
				// ... and if the raycast hits the player...
				if(hit.collider.gameObject == player)
				{
					// ... the player is in sight.
					playerInSight = true;
					
				} else {
					playerInSight = false;
				}
			}
		} else {
			playerInSight = false;
		}
	}
	
	//when the player is 'out of sight'
	void OnTriggerExit (Collider other)
	{
		// If the player leaves the trigger zone...
		if(other.gameObject == player)
			// ... the player is not in sight.
			playerInSight = false;
	}
	
	//determines the path length for the path that the enemy must follow
	float CalculatePathLength (Vector3 targetPosition)
	{
		// Create a path and set it based on a target position.
		NavMeshPath path = new NavMeshPath();
		if(nav.enabled)
			nav.CalculatePath(targetPosition, path);
		
		// Create an array of points which is the length of the number of corners in the path + 2.
		Vector3[] allWayPoints = new Vector3[path.corners.Length + 2];
		
		// The first point is the enemy's position.
		allWayPoints[0] = transform.position;
		
		// The last point is the target position.
		allWayPoints[allWayPoints.Length - 1] = targetPosition;
		
		// The points inbetween are the corners of the path.
		for(int i = 0; i < path.corners.Length; i++)
		{
			allWayPoints[i + 1] = path.corners[i];
		}
		
		// Create a float to store the path length that is by default 0.
		float pathLength = 0;
		
		// Increment the path length by an amount equal to the distance between each waypoint and the next.
		for(int i = 0; i < allWayPoints.Length - 1; i++)
		{
			pathLength += Vector3.Distance(allWayPoints[i], allWayPoints[i + 1]);
		}
		
		return pathLength;
	}
}