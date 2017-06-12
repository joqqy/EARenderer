//
//  SceneObjectsTabView.m
//  EARenderer
//
//  Created by Pavlo Muratov on 05.06.17.
//  Copyright © 2017 MPO. All rights reserved.
//

#import "SceneObjectsTabView.h"

#import "Scene.hpp"

@interface SceneObjectsTabView ()

@property (assign, nonatomic) EARenderer::Scene *scene;

@end

@implementation SceneObjectsTabView

- (void)buildTabsWithScene:(SceneOpaque *)scenePtr
{
    self.scene = &scenePtr->scene;
    
    [self.meshesTab buildOutlineViewWithMeshes:&self.scene->meshes() andSubMeshes:&self.scene->subMeshes()];
}

@end
