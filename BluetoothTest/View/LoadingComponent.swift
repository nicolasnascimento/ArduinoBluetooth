//
//  LoadingView.swift
//  BluetoothTest
//
//  Created by Nicolas Nascimento on 15/02/18.
//  Copyright © 2018 Nicolas Nascimento. All rights reserved.
//

import UIKit

class LoadingComponent {
    
    private let blurViewTag = 1234
    
    func addLoadingIndicator(to parent: UIView) {
        let activityIndicator = UIActivityIndicatorView(activityIndicatorStyle: .gray)
        let blurView = UIVisualEffectView(effect: UIBlurEffect(style: .light))
        
        blurView.tag = blurViewTag
        
        blurView.translatesAutoresizingMaskIntoConstraints = false
        activityIndicator.translatesAutoresizingMaskIntoConstraints = false
        
        
        parent.addSubview(activityIndicator)
        parent.addSubview(blurView)
        activityIndicator.layer.zPosition = 1000
        blurView.layer.zPosition = activityIndicator.layer.zPosition - 1
        
        activityIndicator.topAnchor.constraint(equalTo: parent.topAnchor).isActive = true
        activityIndicator.bottomAnchor.constraint(equalTo: parent.bottomAnchor).isActive = true
        activityIndicator.leftAnchor.constraint(equalTo: parent.leftAnchor).isActive = true
        activityIndicator.rightAnchor.constraint(equalTo: parent.rightAnchor).isActive = true
        
        blurView.topAnchor.constraint(equalTo: parent.topAnchor).isActive = true
        blurView.bottomAnchor.constraint(equalTo: parent.bottomAnchor).isActive = true
        blurView.leftAnchor.constraint(equalTo: parent.leftAnchor).isActive = true
        blurView.rightAnchor.constraint(equalTo: parent.rightAnchor).isActive = true
        
        activityIndicator.startAnimating()
    }
    func removeLoadingIndicators(from parent: UIView) {
        
        // Remove Indicator
        for activityIndicator in parent.subviews.filter({ $0 is UIActivityIndicatorView }) as? [UIActivityIndicatorView] ?? [] {
            activityIndicator.stopAnimating()
            activityIndicator.removeFromSuperview()
        }
        
        // Remove Blur View
        guard let blurView = parent.viewWithTag(blurViewTag) else { return }
        UIView.animate(withDuration: 0.2, animations: {
            blurView.alpha = 0.0
        }) { _ in
            blurView.removeFromSuperview()
        }
    }
}
