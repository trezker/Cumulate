#ifndef contactlistener_h
#define contactlistener_h


class ContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact)
	{
		B2_NOT_USED(contact);
	}
	virtual void EndContact(b2Contact* contact)
	{
		B2_NOT_USED(contact);
	}
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

 		Physic* physicA = reinterpret_cast<Physic*>(fixtureA->GetBody()->GetUserData());
 		Physic* physicB = reinterpret_cast<Physic*>(fixtureB->GetBody()->GetUserData());

		PhysicPlatform* physicplatform = dynamic_cast<PhysicPlatform*>(physicA);
		b2Fixture* platform = NULL;
		b2Fixture* character = NULL;
		if(!physicplatform)
		{
			physicplatform = dynamic_cast<PhysicPlatform*>(physicB);
			if(!physicplatform)
			{
				return;
			}
			else
			{
				platform = fixtureB;
				character = fixtureA;
			}
		}
		else
		{
			platform = fixtureA;
			character = fixtureB;
		}

		b2Vec2 position = character->GetBody()->GetPosition();
		float radius = character->GetShape()->m_radius;

		b2PolygonShape* pshape = dynamic_cast<b2PolygonShape*>(platform->GetShape());
		b2Vec2 lp1 = pshape->GetVertex(0) + platform->GetBody()->GetPosition();
		b2Vec2 lp2 = pshape->GetVertex(1) + platform->GetBody()->GetPosition();
		b2Vec2 le = lp2 - lp1;
		float angle = -atan2(le.y, le.x);
		
		b2Vec2 diff = position - lp1;
		//Rotate point by angle of line and diff.y is the distance.
		b2Vec2 diffr;
		diffr.x = cos(angle)*diff.x - sin(angle)*diff.y;
		diffr.y = sin(angle)*diff.x + cos(angle)*diff.y;

		float platform_max_x = cos(angle)*le.x - sin(angle)*le.y;
		
		//Detects while circle is above the line segment
		if(diffr.x>=0 && diffr.x<platform_max_x && diffr.y + radius > 3.0f * b2_linearSlop)
		{
			contact->SetEnabled(false);
		}
		//Detect at corners
		else if(-diffr.y < radius/2)
		{
			contact->SetEnabled(false);
		}
	}
	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

private:
};

#endif
