//
//  ViewController.m
//  Easy Guitar Tuner
//
//  Created by Apple on 05/12/15.
//  Copyright © 2015 Visne Software. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _imgGuitar.image = [UIImage imageNamed:@"guitarneck.png"];
    //self.view.backgroundColor = [UIColor redColor];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)fE:(id)sender {
    _imgGuitar.image = [UIImage imageNamed:@"guitarneckE.png"];
}
- (IBAction)fA:(id)sender {
    _imgGuitar.image = [UIImage imageNamed:@"guitarneckA.png"];
}

- (IBAction)fD:(id)sender {
    _imgGuitar.image = [UIImage imageNamed:@"guitarneckD.png"];
}

- (IBAction)fG:(id)sender {
    _imgGuitar.image = [UIImage imageNamed:@"guitarneckG.png"];
}

- (IBAction)fB:(id)sender {
    _imgGuitar.image = [UIImage imageNamed:@"guitarneckB.png"];
}

- (IBAction)fEH:(id)sender {
    _imgGuitar.image = [UIImage imageNamed:@"guitarneckEH.png"];
}

@end
