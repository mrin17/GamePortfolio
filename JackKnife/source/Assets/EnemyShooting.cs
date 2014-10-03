using UnityEngine;
using System.Collections;

//ORIGINAL CODE FROM: https://unity3d.com/learn/tutorials/projects/stealth/enemy-shooting

public class EnemyShooting : MonoBehaviour
{
	public float maximumDamage = 120f;                  // The maximum potential damage per shot.
	public float minimumDamage = 45f;                   // The minimum potential damage per shot.
	public AudioClip shotClip;                          // An audio clip to play when a shot happens.
	public float flashIntensity = 3f;                   // The intensity of the light when the shot happens.
	public float fadeSpeed = 10f;                       // How fast the light will fade after the shot.
	
	
	private Animator anim;                              // Reference to the animator.
	private LineRenderer laserShotLine;                 // Reference to the laser shot line renderer.
	private Light laserShotLight;                       // Reference to the laser shot light.
	private SphereCollider col;                         // Reference to the sphere collider.
	private Transform player;                           // Reference to the player's transform.
	private bool shooting;                              // A bool to say whether or not the enemy is currently shooting.
	private float scaledDamage;                         // Amount of damage that is scaled by the distance from the player.
	
	//called once when created
	void Awake ()
	{
		// Setting up the references.
		col = GetComponent<SphereCollider>();
		player = GameObject.Find("Player").transform;
		
		// The scaledDamage is the difference between the maximum and the minimum damage.
		scaledDamage = maximumDamage - minimumDamage;
	}
	
	//called once per frame
	void Update ()
	{
		// Cache the current value of the shot curve.
		float shot = 0.0f;
		
		// If the shot curve is peaking and the enemy is not currently shooting...
		if(shot > 0.5f && !shooting)
			// ... shoot

			Shoot();
		
		// If the shot curve is no longer peaking...
		if(shot < 0.5f)
		{
			// ... the enemy is no longer shooting and disable the line renderer.
			shooting = false;
//			laserShotLine.enabled = false;
		}
	}
	
	//when the enemy shoots
	public void Shoot ()
	{
		// The enemy is shooting.
		shooting = true;
		
		// The fractional distance from the player, 1 is next to the player, 0 is the player is at the extent of the sphere collider.
		float fractionalDistance = (col.radius - Vector3.Distance(transform.position, player.position)) / col.radius;
		
		// The damage is the scaled damage, scaled by the fractional distance, plus the minimum damage.
		float damage = scaledDamage * fractionalDistance + minimumDamage;

		Debug.Log ("DAMAGE: " + damage);
		
		// Play the sound
		AudioSource.PlayClipAtPoint(shotClip, transform.position);
	}

}