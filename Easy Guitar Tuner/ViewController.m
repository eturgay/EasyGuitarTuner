//
//  ViewController.m
//  Easy Guitar Tuner
//
//  Created by Apple on 05/12/15.
//  Copyright © 2015 Visne Software. All rights reserved.
//

#import "ViewController.h"
#import "Audio/AudioUnitReceive.h"
#import "Math/SignalDefinitions.h"
#import "Math/ProcessSignal.h"
#import "Globals/GlobalVariables.hpp"

@interface ViewController ()

@end

@implementation ViewController

int indexBar;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _imgGuitar.image = [UIImage imageNamed:@"guitarneck.png"];
    //self.view.backgroundColor = [UIColor redColor];
    indexBar = 0;
    
    samplingRate = 22000;
    downSamplingFactor  = 1;
    dftLength = 1024;
    dftAvaraging = 1;
    
    initAudioSession();
    initAudioStreams(audioUnit);
    startAudioUnit(audioUnit);
    
    
    _tmUpdate = [NSTimer scheduledTimerWithTimeInterval: 0.02
                                                      target: self
                                                    selector:@selector(update)
                                                    userInfo: nil repeats:YES];
    
}

-(void) update {
    
    Process2(0);
    [self SelectString];
   _lblFirstHarmonic.text = [NSString stringWithFormat:@"%f Hz", firstHarmonic];
}
-(void) SelectString{
    
    if (firstHarmonic < 95)
        _imgGuitar.image = [UIImage imageNamed:@"guitarneckE.png"];
    else if (firstHarmonic >= 95 && firstHarmonic < 128)
        _imgGuitar.image = [UIImage imageNamed:@"guitarneckA.png"];
    else if (firstHarmonic >= 128 && firstHarmonic < 171)
        _imgGuitar.image = [UIImage imageNamed:@"guitarneckD.png"];
    else if (firstHarmonic >= 171 && firstHarmonic < 222)
        _imgGuitar.image = [UIImage imageNamed:@"guitarneckG.png"];
    else if (firstHarmonic >= 222 && firstHarmonic < 346)
        _imgGuitar.image = [UIImage imageNamed:@"guitarneckB.png"];
    else
        _imgGuitar.image = [UIImage imageNamed:@"guitarneckEH.png"];

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

- (IBAction)Increase:(id)sender {
    indexBar++;
    [self UpdateBar];
    
    
}

- (IBAction)decrease:(id)sender {
    indexBar--;
    [self UpdateBar];
}

- (void)UpdateBar {
    switch (indexBar) {
        case 0:
            _imgBar.image = [UIImage imageNamed:@"markerPos0.png"];
            break;
        case 1:
            _imgBar.image = [UIImage imageNamed:@"markerPos1.png"];
            break;
        case 2:
            _imgBar.image = [UIImage imageNamed:@"markerPos2.png"];
            break;
        case 3:
            _imgBar.image = [UIImage imageNamed:@"markerPos3.png"];
            break;
        case 4:
            _imgBar.image = [UIImage imageNamed:@"markerPos4.png"];
            break;
        case -1:
            _imgBar.image = [UIImage imageNamed:@"markerPos_m1.png"];
            break;
        case -2:
            _imgBar.image = [UIImage imageNamed:@"markerPos_m2.png"];
            break;
        case -3:
            _imgBar.image = [UIImage imageNamed:@"markerPos_m3.png"];
            break;
        case -4:
            _imgBar.image = [UIImage imageNamed:@"markerPos_m4.png"];
            break;
            
        default:
            break;
    }
    
}


@end
