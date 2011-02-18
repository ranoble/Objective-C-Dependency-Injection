//
//  DependencyContext.m
//  MacmillanCatalog
//
//  Created by Richard Noble on 18/11/2010.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "DependencyContext.h"



@implementation DependencyContext

SYNTHESIZE_SINGLETON_FOR_CLASS(DependencyContext);

-(id) init{
	if (self = [super init]){
		NSString *filePath = [[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"dependencies.plist"];
		classDefinitionDictionary = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
		objectDictionary = [[NSMutableDictionary alloc] initWithCapacity: classDefinitionDictionary.count];
	}
	return self;
}

//To be overriddent for loading from alternate bundles
-(NSBundle*) getBundle{
	return [NSBundle mainBundle];
}

//Validations still need to be uncommented
-(id) getDependency: (NSString*) dependencyProtocol{
	id dep = [objectDictionary objectForKey:dependencyProtocol];
	if (dep == nil){
		NSString *implementationName = [classDefinitionDictionary objectForKey:dependencyProtocol];
		//if (implementationName == nil) throw Exception
		Class *ImplementationClass = [[self getBundle] classNamed:implementationName];
		dep = [[ImplementationClass alloc] init];
		//if (implementationClass != nil){}
		//if [gribFileDataViewController conformsToProtocol:@protocol(dependencyProtocol)]
		//NSLog([dep description]);
		[objectDictionary setObject:dep forKey:dependencyProtocol];
		[dep release];
		return [objectDictionary objectForKey:dependencyProtocol];
	}
	return dep;
}

-(void) dealloc{
	[classDefinitionDictionary release];
	[objectDictionary release];
}

@end
