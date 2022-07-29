using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateBigCube : MonoBehaviour
    
{
    Vector2 firstPos;
    Vector2 secondPos;
    Vector2 currentSwipe;

    Vector3 previousMousePosition;
    Vector3 mouseDelta;
    // Start is called before the first frame update

    public GameObject target;

    float speed = 200f;


    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Swipe();

        Drag();

    }

    void Drag()
    {
        if (Input.GetMouseButton(1))
        {
            mouseDelta = Input.mousePosition - previousMousePosition;
            mouseDelta *= 0.1f;
            transform.rotation = Quaternion.Euler(mouseDelta.y, -mouseDelta.x, 0) * transform.rotation;

        }

        else
        {
            if (transform.rotation != target.transform.rotation)
            {
                var step = speed * Time.deltaTime;
                transform.rotation = Quaternion.RotateTowards(transform.rotation, target.transform.rotation, step);
            }
        }

        previousMousePosition = Input.mousePosition;

    }

    void Swipe()
    {
        if (Input.GetMouseButtonDown(1))
        {
            //get position 2d of first mouse click
            firstPos = new Vector2(Input.mousePosition.x, Input.mousePosition.y);
            //print(firstPos);
        }

        if (Input.GetMouseButtonUp(1))
        {
            secondPos = new Vector2(Input.mousePosition.x, Input.mousePosition.y);

            currentSwipe = new Vector2(secondPos.x - firstPos.x, secondPos.y - firstPos.y);

            currentSwipe.Normalize();

            if (leftSwipe(currentSwipe))
            {
                target.transform.Rotate(0, 90, 0, Space.World);
            }
            else if (rightSwipe(currentSwipe))
            {
                target.transform.Rotate(0, -90, 0, Space.World);
            }

            else if (upLeftSwipe(currentSwipe))
            {
                target.transform.Rotate(90, 0, 0, Space.World);
            }

            else if (upRightSwipe(currentSwipe))
            {
                target.transform.Rotate(0, 0, -90, Space.World);
            }

            else if (downLeftSwipe(currentSwipe))
            {
                target.transform.Rotate(0, 0, 90, Space.World);
            }

            else if (downRightSwipe(currentSwipe))
            {
                target.transform.Rotate(-90, 0, 0, Space.World);
            }


        }

    }

    bool leftSwipe(Vector2 swipe)
    {
        return currentSwipe.x < 0 && currentSwipe.y > -0.5f && currentSwipe.y < 0.5f;
    }

    bool rightSwipe(Vector2 swipe)
    {
        return currentSwipe.x > 0 && currentSwipe.y > -0.5f && currentSwipe.y < 0.5f;
    }

    bool upLeftSwipe(Vector2 swipe)
    {
        return currentSwipe.y > 0 && currentSwipe.x < 0f;
    }

    bool upRightSwipe(Vector2 swipe)
    {
        return currentSwipe.y > 0 && currentSwipe.x > 0f;
    }

    bool downLeftSwipe(Vector2 swipe)
    {
        return currentSwipe.y < 0 && currentSwipe.x < 0f;
    }

    bool downRightSwipe(Vector2 swipe)
    {
        return currentSwipe.y < 0 && currentSwipe.x > 0f;
    }
}
