//
//  SLSOpenGLES20Renderer.h
//  Molecules
//
//  Created by Brad Larson on 4/12/2011.
//  Copyright 2011 Sunset Lake Software LLC. All rights reserved.
//

#import "SLSOpenGLESRenderer.h"

@class GLProgram;

@interface SLSOpenGLES20Renderer : SLSOpenGLESRenderer 
{
    GLProgram *sphereDepthProgram;
	GLint sphereDepthPositionAttribute, sphereDepthImpostorSpaceAttribute, sphereDepthModelViewMatrix;
    GLint sphereDepthRadius, sphereDepthOrthographicMatrix;
    GLint sphereDepthPrecalculatedDepthTexture;
    
    GLProgram *cylinderDepthProgram;
    GLint cylinderDepthPositionAttribute, cylinderDepthDirectionAttribute, cylinderDepthImpostorSpaceAttribute, cylinderDepthModelViewMatrix;
    GLint cylinderDepthRadius, cylinderDepthOrthographicMatrix;
    
    GLuint depthPassTexture;
    GLuint depthPassRenderbuffer, depthPassFramebuffer, depthPassDepthBuffer;

    GLProgram *sphereRaytracingProgram;
	GLint sphereRaytracingPositionAttribute, sphereRaytracingImpostorSpaceAttribute, sphereRaytracingAOOffsetAttribute, sphereRaytracingModelViewMatrix;
    GLint sphereRaytracingLightPosition, sphereRaytracingRadius, sphereRaytracingColor, sphereRaytracingOrthographicMatrix, sphereRaytracingInverseModelViewMatrix;
    GLint sphereRaytracingDepthTexture, sphereRaytracingPrecalculatedDepthTexture, sphereRaytracingAOTexture, sphereRaytracingTexturePatchWidth;
    
	GLProgram *cylinderRaytracingProgram;
    GLint cylinderRaytracingPositionAttribute, cylinderRaytracingDirectionAttribute, cylinderRaytracingImpostorSpaceAttribute, cylinderRaytracingAOOffsetAttribute, cylinderRaytracingModelViewMatrix;
    GLint cylinderRaytracingLightPosition, cylinderRaytracingRadius, cylinderRaytracingColor, cylinderRaytracingOrthographicMatrix;
    GLint cylinderRaytracingDepthTexture, cylinderRaytracingInverseModelViewMatrix, cylinderRaytracingAOTexture, cylinderRaytracingTexturePatchWidth;
    
    GLProgram *sphereAmbientOcclusionProgram;
	GLint sphereAmbientOcclusionPositionAttribute, sphereAmbientOcclusionImpostorSpaceAttribute, sphereAmbientOcclusionAOOffsetAttribute, sphereAmbientOcclusionModelViewMatrix;
    GLint sphereAmbientOcclusionRadius, sphereAmbientOcclusionOrthographicMatrix, sphereAmbientOcclusionInverseModelViewMatrix, sphereAmbientOcclusionTexturePatchWidth, sphereAmbientOcclusionIntensityFactor;
    GLint sphereAmbientOcclusionDepthTexture, sphereAmbientOcclusionPrecalculatedDepthTexture;

    GLProgram *cylinderAmbientOcclusionProgram;
    GLint cylinderAmbientOcclusionPositionAttribute, cylinderAmbientOcclusionDirectionAttribute, cylinderAmbientOcclusionImpostorSpaceAttribute, cylinderAmbientOcclusionAOOffsetAttribute, cylinderAmbientOcclusionModelViewMatrix;
    GLint cylinderAmbientOcclusionRadius, cylinderAmbientOcclusionOrthographicMatrix, cylinderAmbientOcclusionInverseModelViewMatrix, cylinderAmbientOcclusionTexturePatchWidth, cylinderAmbientOcclusionIntensityFactor;
    GLint cylinderAmbientOcclusionDepthTexture;

    GLuint ambientOcclusionTexture;
    GLuint ambientOcclusionRenderbuffer, ambientOcclusionFramebuffer;
    
    GLuint sphereDepthMappingTexture;

    GLfloat previousAmbientOcclusionOffset[2];
    GLfloat lightDirection[3];
    GLfloat orthographicMatrix[16];
    
    unsigned int widthOfAtomAOTexturePatch;
    GLfloat normalizedAOTexturePatchWidth;
}

// OpenGL drawing support
- (void)initializeShaders;
- (void)loadOrthoMatrix:(GLfloat *)matrix left:(GLfloat)left right:(GLfloat)right bottom:(GLfloat)bottom top:(GLfloat)top near:(GLfloat)near far:(GLfloat)far;
- (BOOL)createFramebuffer:(GLuint *)framebufferPointer size:(CGSize)bufferSize renderBuffer:(GLuint *)renderbufferPointer depthBuffer:(GLuint *)depthbufferPointer texture:(GLuint *)backingTexturePointer layer:(CAEAGLLayer *)layer;
- (void)switchToDisplayFramebuffer;
- (void)switchToDepthPassFramebuffer;
- (void)switchToAmbientOcclusionFramebuffer;
- (void)generateSphereDepthMapTexture;

// Molecule 3-D geometry generation
- (void)addTextureCoordinate:(GLfloat *)newTextureCoordinate forAtomType:(SLSAtomType)atomType;
- (void)addAmbientOcclusionTextureOffset:(GLfloat *)ambientOcclusionOffset forAtomType:(SLSAtomType)atomType;
- (void)addBondDirection:(GLfloat *)newDirection;
- (void)addBondTextureCoordinate:(GLfloat *)newTextureCoordinate;
- (void)addBondAmbientOcclusionTextureOffset:(GLfloat *)ambientOcclusionOffset;

// OpenGL drawing routines
- (void)renderDepthTextureForModelViewMatrix:(GLfloat *)depthModelViewMatrix;
- (void)renderRaytracedSceneForModelViewMatrix:(GLfloat *)raytracingModelViewMatrix inverseMatrix:(GLfloat *)inverseMatrix;
- (void)renderAmbientOcclusionTextureForModelViewMatrix:(GLfloat *)ambientOcclusionModelViewMatrix inverseMatrix:(GLfloat *)inverseMatrix fractionOfTotal:(GLfloat)fractionOfTotal;
- (void)prepareAmbientOcclusionMap;

@end