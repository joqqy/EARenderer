//
//  MaterialLoader.h
//  EARenderer
//
//  Created by Pavlo Muratov on 31.05.2018.
//  Copyright © 2018 MPO. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SharedResourceStorage.hpp"

@interface MaterialLoader : NSObject

+ (EARenderer::MaterialReference)load_sandFloor_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_marbleTiles_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_testBricks_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_bricks08_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_fabric05_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_fabric06_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_BlueFabric_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_RedFabric_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_rocks01_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_pavingStones09_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_pavingStones10_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

+ (EARenderer::MaterialReference)load_WetStones_MaterialToPool:(EARenderer::SharedResourceStorage *)pool;

@end
