precision mediump float;

uniform sampler2D depthTexture;
uniform mediump mat4 modelViewProjMatrix;
uniform mediump mat4 inverseModelViewProjMatrix;
uniform mediump float intensityFactor;

varying mediump vec2 impostorSpaceCoordinate;
varying mediump vec2 depthLookupCoordinate;
varying mediump vec3 normalizedStartingCoordinate;
varying mediump vec3 normalizedEndingCoordinate;
varying mediump float halfCylinderRadius;
varying mediump vec3 adjustmentForOrthographicProjection;

const mediump float oneThird = 1.0 / 3.0;

mediump float depthFromEncodedColor(mediump vec4 encodedColor)
{
    return oneThird * (encodedColor.r + encodedColor.g + encodedColor.b);
    //    return encodedColor.r;
}

mediump vec3 coordinateFromTexturePosition(mediump vec2 texturePosition)
{
    float halfS = texturePosition.s / 2.0;
    
    if (texturePosition.s >= 0.0)
    {
        return vec3(1.0 - abs(2.0 * texturePosition.s - 1.0), 2.0 * texturePosition.s - 1.0, texturePosition.t);
    }
    else
    {
        return vec3(abs(2.0 * texturePosition.s - 1.0) - 1.0, 2.0 * texturePosition.s - 1.0, texturePosition.t);
    }
    
}

void main()
{
    vec3 currentCylinderSurfaceCoordinate = coordinateFromTexturePosition(impostorSpaceCoordinate);
    float fractionalZPosition = (currentCylinderSurfaceCoordinate.z + 1.0) / 2.0;

    vec3 currentBaseCoordinate = (normalizedEndingCoordinate * fractionalZPosition) + (normalizedStartingCoordinate * (1.0 - fractionalZPosition));
    vec2 offsetXYCoordinates = normalize(currentCylinderSurfaceCoordinate.xy);
    
    vec3 currentPositionCoordinate = currentBaseCoordinate - halfCylinderRadius * (vec3(0.0, 0.0, 1.0) * adjustmentForOrthographicProjection);
//    vec3 currentPositionCoordinate = currentBaseCoordinate;
    
    float previousDepthValue = depthFromEncodedColor(texture2D(depthTexture, currentPositionCoordinate.xy));
    
    //    gl_FragColor = vec4(texture2D(depthTexture, currentPositionCoordinate.xy).rgb, 1.0);
    
    //    gl_FragColor = vec4(currentSphereSurfaceCoordinate, 1.0);
    
    if ( (floor(currentPositionCoordinate.z * 765.0) - 1.0) <= (ceil(previousDepthValue * 765.0)) )
    {
        //        gl_FragColor = vec4(vec3(previousDepthValue - currentPositionCoordinate.z), 1.0);
//        gl_FragColor = vec4(currentPositionCoordinate.z, previousDepthValue, 0.0, 1.0);
        gl_FragColor = vec4(vec3(intensityFactor), 1.0);
    }
    else
    {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
 //   gl_FragColor = vec4(currentCylinderSurfaceCoordinate, 1.0);
//   gl_FragColor = vec4(currentBaseCoordinate, 1.0);
 //   gl_FragColor = vec4(vec3(fractionalZPosition), 1.0);
}