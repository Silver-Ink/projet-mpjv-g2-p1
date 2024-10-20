#include "SpringRod.h"

void SpringRod::updateForce(Particle* _otherParticle, float _dt)
{
    Vec3 direction = _otherParticle->getPos() - particle->getPos();
    float currentLength = direction.length();
    
	// debug currentLength and rodLength
	
    if (currentLength > rodLength)
    {
        // Normalisation du vecteur de direction
        direction *= 1.0f / currentLength;

        // Calcul de la force de correction
        Vec3 correctionForce = direction * (currentLength - rodLength) * .01;

        // Limiter la force maximale pour éviter les surcorrections
        float maxForce = 100.0f; // Ajuste cette valeur en fonction de ton système
        if (correctionForce.length() > maxForce)
        {
            correctionForce *= maxForce / correctionForce.length();
        }

        // Application de la force corrigée
        _otherParticle->addForce(-1*correctionForce);
        particle->addForce(correctionForce);
    }

    else if (currentLength < rodLength) 
    {
		_otherParticle->clearAccum();
		particle->clearAccum();
    }
}


void SpringRod::drawForce(Particle* _otherParticle)
{
	ofSetLineWidth(5.);
	ofSetColor(ofColor::darkGrey);
	ofDrawLine((glm::vec2)_otherParticle->getPos(), (glm::vec2)particle->getPos());
}