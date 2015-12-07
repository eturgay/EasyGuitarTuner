//
//  ViewController.h
//  Easy Guitar Tuner
//
//  Created by Apple on 05/12/15.
//  Copyright © 2015 Visne Software. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UIImageView *imgGuitar;
- (IBAction)fE:(id)sender;
- (IBAction)fA:(id)sender;
- (IBAction)fD:(id)sender;
- (IBAction)fG:(id)sender;
- (IBAction)fB:(id)sender;
- (IBAction)fEH:(id)sender;

@end

